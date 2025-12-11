#ifndef THI_SINH_DAO_H
#define THI_SINH_DAO_H

#include <QDate>

#include "db/models/thi_sinh.h"
#include "utils/string.h"

#include "utils/string.h"
#include "ui/custom_message_box.h"
#include "db/diem_thi_sat_dao.h"
#include "db/diem_hocba_dao.h"
#include "db/chungchi_tienganh_dao.h"
#include "db/ma_chungchinn_dao.h"
#include "db/ptxt_dao.h"
#include "db/monhoc_dao.h"

static uint page = 0;
static uint count = 100;

inline uint getThiSinhPageCount(){
    uint page = qCeil(qx::dao::count<thi_sinh_ptr>()/count);
    return page;
}

inline void setThiSinhPage(uint &_page){
    page = _page - 1;
}

inline bool addThiSinh(QString &cccd, QString &ho_ten,
                       QDate &ngay_sinh, QString &gioi_tinh,
                       QString &dia_chi, QString &email, QString &sdt, QString &sbd ){
    thi_sinh_ptr adding;
    adding.reset(new thi_sinh());
    adding->cccd = cccd;
    adding->ho_ten = ho_ten;
    adding->ngay_sinh = ngay_sinh;
    adding->gioi_tinh = gioi_tinh;
    adding->dia_chi = dia_chi;
    adding->email = email;
    adding->sdt = sdt;
    adding->sbd = sbd;

    trimLeadingAndTrailing(adding->cccd);
    trimLeadingAndTrailing(adding->ho_ten);
    trimLeadingAndTrailing(adding->sdt);
    trimLeadingAndTrailing(adding->sbd);

    //if (!isPhoneNumberValid(adding->sdt)) return false;

    QSqlError err = qx::dao::insert(adding);
    if (err.isValid())
        return false;
    else
        return true;
}

inline bool changeThiSinh(thi_sinh_ptr &item, QString &cccd, QString &ho_ten,
                          QDate &ngay_sinh, QString &gioi_tinh,
                          QString &dia_chi, QString &email, QString &sdt, QString &sbd){
    item->cccd = cccd;
    item->ho_ten = ho_ten;
    item->ngay_sinh = ngay_sinh;
    item->gioi_tinh = gioi_tinh;
    item->dia_chi = dia_chi;
    item->email = email;
    item->sdt = sdt;
    item->sbd = sbd;

    trimLeadingAndTrailing(item->cccd);
    trimLeadingAndTrailing(item->ho_ten);
    trimLeadingAndTrailing(item->sdt);
    trimLeadingAndTrailing(item->sbd);

    if (!isPhoneNumberValid(item->sdt)) return false;

    QSqlError err = qx::dao::update(item);
    if (err.isValid())
        return false;
    else
        return true;
}

inline std::optional<QList<thi_sinh_ptr>> getAllThiSinh(){
    QList<thi_sinh_ptr> list;

    qx_query query;
    query.limit(count, page*count);
    QSqlError err = qx::dao::fetch_by_query(query, list);

    if (err.isValid()) {
        // qDebug() << "Error:" << err.text();
        return std::nullopt;
    } else {
        return list;
    }
}

inline std::optional<thi_sinh_ptr> getThiSinhByCCCD(QString &cccd){
    QList<thi_sinh_ptr> list;
    qx_query query;
    query.where("so_cccd").isEqualTo(QVariant::fromValue(cccd));
    QSqlError err = qx::dao::fetch_by_query(query, list);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return std::nullopt;
    } else {
        if (list.isEmpty()) return std::nullopt;
        return list.first();
    }
}

inline std::optional<thi_sinh_ptr> getThiSinhById(long &id){
    thi_sinh_ptr item = std::make_shared<thi_sinh>(id);
    QSqlError err = qx::dao::fetch_by_id(item);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return std::nullopt;
    } else {
        return item;
    }
}

inline bool deleteThiSinhById(long &id){
    auto item = getThiSinhById(id);
    if (!item) return false;
    QSqlError err = qx::dao::delete_by_id(*item);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return false;
    } else {
        return true;
    }
}

inline void importDiemSat(QString &path){
    qx::QxSession session;
    int index = 3;
    auto rows = readExcel(path);

    if (rows->first().length() != 11 || !rows){
        custom_message_box("", "Format excel không hợp lệ", custom_message_box::Error).exec();
        return;
    }else{
        for (auto &row : *rows){
            thi_sinh_ptr adding;
            adding.reset(new thi_sinh());
            for (auto &string : row) trimLeadingAndTrailing(string);

            while (true){
                auto thi_sinh_opt = getThiSinhByCCCD(row[1]);
                if ( thi_sinh_opt){
                    adding=  thi_sinh_opt.value();
                    adding->ho_ten = row[0];
                    adding->cccd = row[1];
                    adding->ngay_sinh = QDate::fromString(row[2], "dd/MM/yyyy");
                    adding->gioi_tinh = row[3];
                    changeThiSinh(adding, adding->cccd, adding->ho_ten, adding->ngay_sinh, adding->gioi_tinh, adding->dia_chi, adding->email, adding->sdt, adding->sdt);
                    break;
                }else{
                    adding->ho_ten = row[0];
                    adding->cccd = row[1];
                    adding->ngay_sinh = QDate::fromString(row[2], "dd/MM/yyyy");
                    adding->gioi_tinh = row[3];
                    addThiSinh(adding->cccd, adding->ho_ten, adding->ngay_sinh, adding->gioi_tinh, adding->dia_chi, adding->email, adding->sdt, adding->sdt);
                }
            }
            qDebug() << "phase 2";
            diem_thi_sat_ptr sat;
            sat.reset(new diem_thi_sat());
            sat->thi_sinh = adding;
            sat->diem = row[4].toFloat();
            sat->ma_dvtctdl = row[5];
            sat->ten_dvtctdl = row[6];
            auto ptxt_opt = getPtxtByName(row[7]);
            if (!ptxt_opt){
                custom_message_box("", "Phương thức xét tuyển không tồn tại. Lỗi ở hàng "+QString::number(index)+" trong file excel", custom_message_box::Error).exec();
                return;
            }
            sat->ptxt = ptxt_opt.value();

            session += qx::dao::insert(sat, session.database());
            if (!session.isValid()){
                custom_message_box("", "Có lỗi xảy ra khi thêm. Lỗi ở hàng "+QString::number(index)+" trong file excel", custom_message_box::Error).exec();
                return;
                break;
            }
            ++index;
        }
    }
}

inline void importCCNN(QString &path){
    qx::QxSession session;
    int index = 3;
    auto rows = readExcel(path);

    if (rows->first().length() != 9 || !rows){
        custom_message_box("", "Format excel không hợp lệ", custom_message_box::Error).exec();
        return;
    }else{
        for (auto &row : *rows){
            thi_sinh_ptr adding;
            adding.reset(new thi_sinh());
            for (auto &string : row) trimLeadingAndTrailing(string);

            while (true){
                auto thi_sinh_opt = getThiSinhByCCCD(row[1]);
                if ( thi_sinh_opt){
                    adding=  thi_sinh_opt.value();
                    adding->sbd = row[0];
                    changeThiSinh(adding, adding->cccd, adding->ho_ten, adding->ngay_sinh, adding->gioi_tinh, adding->dia_chi, adding->email, adding->sdt, adding->sdt);
                    break;
                }else{
                    adding->cccd = row[1];
                    adding->sbd = row[0];
                    addThiSinh(adding->cccd, adding->ho_ten, adding->ngay_sinh, adding->gioi_tinh, adding->dia_chi, adding->email, adding->sdt, adding->sdt);
                }
            }

            chungchi_tienganh_ptr ccnn;
            ccnn.reset(new chungchi_tienganh());
            while (true){
                auto ccnn_opt = getMaChungchinnName(row[2]);
                if (ccnn_opt){
                    ccnn->ccnn = ccnn_opt.value();
                    break;
                }else{
                    ma_chungchinn_ptr ma_ccnn;
                    ma_ccnn.reset(new ma_chungchinn());
                    ma_ccnn->ma = row[4];
                    ma_ccnn->ten = row[2];
                    addMaChungchinn(ma_ccnn->ma, ma_ccnn->ten);
                }
            }

            ccnn->thi_sinh = adding;
            ccnn->diem = row[3].toFloat();
            auto ptxt_opt = getPtxtByName(row[8]);
            if (!ptxt_opt){
                custom_message_box("", "Phương thức xét tuyển không tồn tại. Lỗi ở hàng "+QString::number(index)+" trong file excel", custom_message_box::Error).exec();
                return;
            }
            ccnn->ptxt = ptxt_opt.value();


            session += qx::dao::insert(ccnn, session.database());
            if (!session.isValid()){
                custom_message_box("", "Có lỗi xảy ra khi thêm. Lỗi ở hàng "+QString::number(index)+" trong file excel", custom_message_box::Error).exec();
                return;
                break;
            }
            ++index;
        }
    }
}

inline void importHocBa(QString &path){
    qx::QxSession session;
    int index = 3;
    auto rows = readExcel(path);

    if (rows->first().length() < 6 || !rows){
        custom_message_box("", "Format excel không hợp lệ", custom_message_box::Error).exec();
        return;
    }else{
        auto monhoc_name_list = *readHocBaMonHoc(path);
        QList<mon_hoc_ptr> monhoc_list;
        for (auto &string : monhoc_name_list) trimLeadingAndTrailing(string);
        for (int i = 0; i < monhoc_name_list.length(); ++i){
            while (true) {
                auto monhoc_opt = getMonHocByName(monhoc_name_list[i]);
                if (monhoc_opt){
                    monhoc_list.append(*monhoc_opt);
                    break;
                }else{
                    addMonHoc(monhoc_name_list[i]);
                }
            }
        }

        for (auto &row : *rows){
            thi_sinh_ptr ts;
            ts.reset(new thi_sinh());
            for (auto &string : row) trimLeadingAndTrailing(string);

            while (true){
                auto thi_sinh_opt = getThiSinhByCCCD(row[2]);
                if ( thi_sinh_opt){
                    ts=  thi_sinh_opt.value();
                    ts->cccd = row[2];
                    ts->ho_ten = row[1];
                    ts->ngay_sinh = QDate::fromString(row[3], "dd/MM/yyyy");
                    ts->gioi_tinh = row[4];
                    changeThiSinh(ts, ts->cccd, ts->ho_ten, ts->ngay_sinh, ts->gioi_tinh, ts->dia_chi, ts->email, ts->sdt, ts->sdt);
                    break;
                }else{
                    ts->cccd = row[2];
                    ts->ho_ten = row[1];
                    ts->ngay_sinh = QDate::fromString(row[3], "dd/MM/yyyy");
                    ts->gioi_tinh = row[4];
                    addThiSinh(ts->cccd, ts->ho_ten, ts->ngay_sinh, ts->gioi_tinh, ts->dia_chi, ts->email, ts->sdt, ts->sdt);
                }
            }


            short lop = row[5].toShort();
            for (int i = 6; i < row.length(); i++){
                if (!row[i].isEmpty()){
                    while (true) {
                        qDebug() << monhoc_list[i-6]->ten_monhoc;
                        auto diem_hocba_opt = getDiemHocbaByThiSinhIdAndName(ts->id, monhoc_list[i-6]->id_monhoc);
                        if (diem_hocba_opt){
                            auto dhb = diem_hocba_opt.value();
                            switch (lop) {
                            case 10:
                                dhb->lop10 = row[i].toFloat();
                                break;
                            case 11:
                                dhb->lop11 = row[i].toFloat();
                                break;
                            case 12:
                                dhb->lop12 = row[i].toFloat();
                                break;
                            }
                            session += qx::dao::update(dhb, session.database());
                        }else{
                            diem_hocba_ptr dhb;
                            dhb.reset(new diem_hocba());
                            dhb->thi_sinh = ts;
                            dhb->mon_hoc = monhoc_list[i-6];
                            switch (lop) {
                            case 10:
                                dhb->lop10 = row[i].toFloat();
                                break;
                            case 11:
                                dhb->lop11 = row[i].toFloat();
                                break;
                            case 12:
                                dhb->lop12 = row[i].toFloat();
                                break;
                            }
                            addDiemHocba(dhb->thi_sinh->id, dhb->mon_hoc->id_monhoc, dhb->lop10, dhb->lop11, dhb->lop12);
                        }
                        if (!session.isValid()){
                            custom_message_box("", "Có lỗi xảy ra khi thêm. Lỗi ở hàng "+QString::number(index)+" trong file excel", custom_message_box::Error).exec();
                            return;
                            break;
                        }
                        break;
                    }
                }
            }


            ++index;
        }
    }
}

#endif // THI_SINH_DAO_H
