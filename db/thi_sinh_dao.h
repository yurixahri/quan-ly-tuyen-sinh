#ifndef THI_SINH_DAO_H
#define THI_SINH_DAO_H

#include <QDate>
#include <QApplication>

#include "db/models/thi_sinh.h"
#include "utils/string.h"

#include "utils/string.h"
#include "ui/custom_message_box.h"
#include "ui/components/progressbar.h"
#include "db/diem_thi_sat_dao.h"
#include "db/diem_hocba_dao.h"
#include "db/chungchi_tienganh_dao.h"
#include "db/doat_giai_dao.h"
#include "db/ma_thanhtich_dao.h"
#include "db/ma_chungchinn_dao.h"
#include "db/ma_nganh_dao.h"
#include "db/ptxt_dao.h"
#include "db/monhoc_dao.h"

#include "db/ma_dtut_dao.h"
#include "db/ma_kvut_dao.h"
#include "db/uutien_dao.h"
#include "db/dang_ky_xet_tuyen_dao.h"

static uint page = 0;
static uint count = 100;
static QString search = "";

inline void setThiSinhSearchValue(QString &_search){
    search = _search;
}

inline uint getThiSinhCount(){
    auto total = qx::dao::count<thi_sinh_ptr>();
    return total;
}

inline uint getThiSinhCountWithQuery(){
    qx_query query("where unaccent(lower(ho_ten)) ilike '%' || unaccent(lower(:ten)) || '%' or so_cccd ilike :cccd");
    query.bind(":ten", search);
    query.bind(":cccd", "%"+search+"%");

    auto total = qx::dao::count<thi_sinh_ptr>(query);
    return total;
}

inline uint getThiSinhPageCount(){
    auto total = getThiSinhCountWithQuery();
    uint page = total/count;
    if (total%count != 0) ++page;
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

    qx_query query("where unaccent(lower(ho_ten)) ilike '%' || unaccent(lower(:ten)) || '%' or so_cccd ilike :cccd order by ho_ten asc"
                   " limit :limit offset :offset");
    query.bind(":ten", "%"+search+"%");
    query.bind(":cccd", "%"+search+"%");
    query.bind(":limit", count);
    query.bind(":offset", page*count);

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
        progressBar progress_bar;
        progress_bar.setInitValue(rows->length());
        progress_bar.show();
        for (auto &row : *rows){
            if (progress_bar.is_closed){
                session.rollback();
                return;
            }

            thi_sinh_ptr adding;
            adding.reset(new thi_sinh());
            for (auto &string : row) string = string.trimmed();

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

            diem_thi_sat_ptr sat;
            sat.reset(new diem_thi_sat());
            sat->thi_sinh = adding;
            sat->diem = row[4].toFloat();
            sat->ma_dvtctdl = row[5];
            sat->ten_dvtctdl = row[6];
            auto ptxt_opt = getPtxtByName(row[7]);
            if (!ptxt_opt){
                progress_bar.close();
                session.rollback();
                custom_message_box("", "Phương thức xét tuyển không tồn tại. Lỗi ở hàng "+QString::number(index)+" trong file excel", custom_message_box::Error).exec();
                return;
            }
            sat->ptxt = ptxt_opt.value();

            doat_giai_ptr doatgiai;
            doatgiai.reset(new doat_giai());
            while (true){
                if (row[8].isEmpty()) break;
                auto thanhtich_opt = getMaThanhTichByName(row[8]);
                if (thanhtich_opt){
                    doatgiai->thanh_tich = thanhtich_opt.value();
                    break;
                }else{
                    ma_thanhtich_ptr thanhtich;
                    thanhtich.reset(new ma_thanhtich());
                    thanhtich->ma = row[8];
                    thanhtich->diem = row[10].toFloat();
                    addMaThanhTich(thanhtich->ma, thanhtich->ten, thanhtich->diem);
                }
            }
            doatgiai->thi_sinh = adding;
            auto monhoc_opt = getMonHocByName(row[9]);
            if (!monhoc_opt){
                progress_bar.close();
                session.rollback();
                custom_message_box("", "Môn đạt giải không tồn tại. Lỗi ở hàng "+QString::number(index)+" trong file excel", custom_message_box::Error).exec();
                return;
            }
            doatgiai->mon_hoc = monhoc_opt.value();

            session += qx::dao::insert(doatgiai, session.database());
            session += qx::dao::insert(sat, session.database());
            if (!session.isValid()){
                progress_bar.close();
                custom_message_box("", "Có lỗi xảy ra khi thêm. Lỗi ở hàng "+QString::number(index)+" trong file excel", custom_message_box::Error).exec();
                return;
            }
            ++index;
            progress_bar.setCurrentValue(index-3);
            QApplication::processEvents();
        }
        progress_bar.close();
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
        progressBar progress_bar;
        progress_bar.setInitValue(rows->length());
        progress_bar.show();
        for (auto &row : *rows){
            if (progress_bar.is_closed){
                session.rollback();
                return;
            }

            thi_sinh_ptr adding;
            adding.reset(new thi_sinh());
            for (auto &string : row) string = string.trimmed();

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
                progress_bar.close();
                session.rollback();
                custom_message_box("", "Phương thức xét tuyển không tồn tại. Lỗi ở hàng "+QString::number(index)+" trong file excel", custom_message_box::Error).exec();
                return;
            }
            ccnn->ptxt = ptxt_opt.value();

            doat_giai_ptr doatgiai;
            doatgiai.reset(new doat_giai());
            while (true){
                if (row[5].isEmpty()) break;
                auto thanhtich_opt = getMaThanhTichByName(row[5]);
                if (thanhtich_opt){
                    doatgiai->thanh_tich = thanhtich_opt.value();
                    break;
                }else{
                    ma_thanhtich_ptr thanhtich;
                    thanhtich.reset(new ma_thanhtich());
                    thanhtich->ma = row[5];
                    thanhtich->diem = row[7].toFloat();
                    addMaThanhTich(thanhtich->ma, thanhtich->ten, thanhtich->diem);
                }
            }
            doatgiai->thi_sinh = adding;
            auto monhoc_opt = getMonHocByName(row[6]);
            if (!monhoc_opt){
                progress_bar.close();
                session.rollback();
                custom_message_box("", "Môn đạt giải không tồn tại. Lỗi ở hàng "+QString::number(index)+" trong file excel", custom_message_box::Error).exec();
                return;
            }
            doatgiai->mon_hoc = monhoc_opt.value();

            session += qx::dao::insert(doatgiai, session.database());
            session += qx::dao::insert(ccnn, session.database());
            if (!session.isValid()){
                custom_message_box("", "Có lỗi xảy ra khi thêm. Lỗi ở hàng "+QString::number(index)+" trong file excel", custom_message_box::Error).exec();
                return;
                break;
            }
            ++index;
            progress_bar.setCurrentValue(index-3);
            QApplication::processEvents();
        }
        progress_bar.close();
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
        for (auto &string : monhoc_name_list) string = string.trimmed();
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

        progressBar progress_bar;
        progress_bar.setInitValue(rows->length());
        progress_bar.show();
        for (auto &row : *rows){
            if (progress_bar.is_closed){
                return;
            }

            thi_sinh_ptr ts;
            ts.reset(new thi_sinh());
            for (auto &string : row) string = string.trimmed();

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
                    qDebug() << lop << row[i].toFloat();
                    while (true) {
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
                            qx::dao::save(dhb);
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
                            progress_bar.close();
                            custom_message_box("", "Có lỗi xảy ra khi thêm. Lỗi ở hàng "+QString::number(index)+" trong file excel", custom_message_box::Error).exec();
                            return;
                            break;
                        }
                        break;
                    }
                }
            }

            ++index;
            progress_bar.setCurrentValue(index-3);
            QApplication::processEvents();
        }
        progress_bar.close();
    }
}


inline void importDoatGiai(QString &path){
    qx::QxSession session;
    int index = 3;
    auto rows = readExcel(path);

    if (rows->first().length() != 8 || !rows){
        custom_message_box("", "Format excel không hợp lệ", custom_message_box::Error).exec();
        return;
    }else{
        progressBar progress_bar;
        progress_bar.setInitValue(rows->length());
        progress_bar.show();
        for (auto &row : *rows){
            if (progress_bar.is_closed){
                session.rollback();
                return;
            }

            thi_sinh_ptr adding;
            adding.reset(new thi_sinh());
            for (auto &string : row) string = string.trimmed();

            while (true){
                auto thi_sinh_opt = getThiSinhByCCCD(row[3]);
                if ( thi_sinh_opt){
                    adding=  thi_sinh_opt.value();
                    adding->ho_ten = row[0]+ " " + row[1];
                    adding->gioi_tinh = row[2];
                    changeThiSinh(adding, adding->cccd, adding->ho_ten, adding->ngay_sinh, adding->gioi_tinh, adding->dia_chi, adding->email, adding->sdt, adding->sdt);
                    break;
                }else{
                    adding->cccd = row[3];
                    adding->ho_ten = row[0]+ " " + row[1];
                    adding->gioi_tinh = row[2];
                    addThiSinh(adding->cccd, adding->ho_ten, adding->ngay_sinh, adding->gioi_tinh, adding->dia_chi, adding->email, adding->sdt, adding->sdt);
                }
            }

            doat_giai_ptr doatgiai;
            doatgiai.reset(new doat_giai());
            while (true){
                if (row[4].isEmpty()) break;
                auto thanhtich_opt = getMaThanhTichByName(row[4]);
                if (thanhtich_opt){
                    doatgiai->thanh_tich = thanhtich_opt.value();
                    break;
                }else{
                    ma_thanhtich_ptr thanhtich;
                    thanhtich.reset(new ma_thanhtich());
                    thanhtich->ma = row[4];
                    addMaThanhTich(thanhtich->ma, thanhtich->ten, thanhtich->diem);
                }
            }

            doatgiai->thi_sinh = adding;
            doatgiai->diem_thanh_tich = row[6].toFloat();

            auto ptxt_opt = getPtxtByName(row[7]);
            if (!ptxt_opt){
                progress_bar.close();
                session.rollback();
                custom_message_box("", "Phương thức xét tuyển không tồn tại. Lỗi ở hàng "+QString::number(index)+" trong file excel", custom_message_box::Error).exec();
                return;
            }
            doatgiai->ptxt = ptxt_opt.value();

            auto monhoc_opt = getMonHocByName(row[5]);
            if (!monhoc_opt){
                progress_bar.close();
                session.rollback();
                custom_message_box("", "Môn đạt giải không tồn tại. Lỗi ở hàng "+QString::number(index)+" trong file excel", custom_message_box::Error).exec();
                return;
            }
            doatgiai->mon_hoc = monhoc_opt.value();


            session += qx::dao::insert(doatgiai, session.database());
            if (!session.isValid()){
                custom_message_box("", "Có lỗi xảy ra khi thêm. Lỗi ở hàng "+QString::number(index)+" trong file excel", custom_message_box::Error).exec();
                return;
            }

            ++index;
            progress_bar.setCurrentValue(index-3);
            QApplication::processEvents();
        }
        progress_bar.close();
    }
}

inline void importUutien(QString &path){
    qx::QxSession session;
    int index = 3;
    auto rows = readExcel(path);

    if (rows->first().length() != 9 || !rows){
        custom_message_box("", "Format excel không hợp lệ", custom_message_box::Error).exec();
        return;
    }else{
        progressBar progress_bar;
        progress_bar.setInitValue(rows->length());
        progress_bar.show();
        for (auto &row : *rows){
            if (progress_bar.is_closed){
                session.rollback();
                return;
            }

            thi_sinh_ptr adding;
            adding.reset(new thi_sinh());
            for (auto &string : row) string = string.trimmed();

            while (true){
                auto thi_sinh_opt = getThiSinhByCCCD(row[2]);
                if ( thi_sinh_opt){
                    adding = thi_sinh_opt.value();
                    adding->ho_ten = row[1];
                    adding->sbd = row[0];
                    adding->gioi_tinh = row[4];
                    adding->ngay_sinh = QDate::fromString(row[3], "dd/MM/yyyy");
                    changeThiSinh(adding, adding->cccd, adding->ho_ten, adding->ngay_sinh, adding->gioi_tinh, adding->dia_chi, adding->email, adding->sdt, adding->sdt);
                    break;
                }else{
                    adding->cccd = row[2];
                    adding->ho_ten = row[1];
                    adding->sbd = row[0];
                    adding->gioi_tinh = row[4];
                    adding->ngay_sinh = QDate::fromString(row[3], "dd/MM/yyyy");
                    addThiSinh(adding->cccd, adding->ho_ten, adding->ngay_sinh, adding->gioi_tinh, adding->dia_chi, adding->email, adding->sdt, adding->sdt);
                }
            }

            uutien_ptr ut;
            ut.reset(new uutien());
            ut->thi_sinh = adding;
            if (!row[5].isEmpty()){
                while (true) {
                    auto ma_dtut_opt = getMaDtutByName(row[5]);
                    if (ma_dtut_opt){
                        ut->dtut = ma_dtut_opt.value();
                        //ut->dtut->diem = row[6].toFloat();
                        // changeMaDtut(ut->dtut, ut->dtut->ma, ut->dtut->ten, ut->dtut->diem);
                        break;
                    }else{
                        ma_dtut_ptr dtut;
                        dtut.reset(new ma_dtut());
                        dtut->ma = row[5];
                        dtut->diem = row[6].toFloat();
                        addMaDtut(dtut->ma, dtut->ten, dtut->diem);
                    }
                }
            }

            if (!row[7].isEmpty()){
                while (true) {
                    auto ma_kvut_opt = getMaKvutByName(row[7]);
                    if (ma_kvut_opt){
                        ut->kvut = ma_kvut_opt.value();
                        // ut->kvut->diem = row[8].toFloat();
                        //changeMaKvut(ut->kvut, ut->kvut->ma, ut->kvut->ten, ut->kvut->diem);
                        break;
                    }else{
                        ma_kvut_ptr kvut;
                        kvut.reset(new ma_kvut());
                        kvut->ma = row[7];
                        kvut->diem = row[8].toFloat();
                        addMaKvut(kvut->ma, kvut->ten, kvut->diem);
                    }
                }
            }


            QSqlError err = qx::dao::insert(ut);
            if (err.isValid()){

            }

            ++index;
            progress_bar.setCurrentValue(index-3);
            QApplication::processEvents();
        }
        progress_bar.close();
    }
}

inline void importNguyenVong(QString &path){
    qx::QxSession session;
    int index = 3;
    auto rows = readExcel(path);

    if (rows->first().length() < 4 || !rows){
        custom_message_box("", "Format excel không hợp lệ", custom_message_box::Error).exec();
        return;
    }else{
        progressBar progress_bar;
        progress_bar.setInitValue(rows->length());
        progress_bar.show();
        for (auto &row : *rows){
            if (progress_bar.is_closed){
                session.rollback();
                return;
            }

            thi_sinh_ptr adding;
            adding.reset(new thi_sinh());
            for (auto &string : row) string = string.trimmed();

            while (true){
                auto thi_sinh_opt = getThiSinhByCCCD(row[0]);
                if (thi_sinh_opt){
                    adding = thi_sinh_opt.value();
                    break;
                }else{
                    adding->cccd = row[0];
                    addThiSinh(adding->cccd, adding->ho_ten, adding->ngay_sinh, adding->gioi_tinh, adding->dia_chi, adding->email, adding->sdt, adding->sdt);
                }
            }

            dang_ky_xet_tuyen_ptr dkxt;
            dkxt.reset(new dang_ky_xet_tuyen());

            auto ma_nganh_opt = getMaNganhByName(row[2]);
            if (!ma_nganh_opt){
                progress_bar.close();
                session.rollback();
                custom_message_box("", "Mã ngành không tồn tại. Lỗi ở hàng "+QString::number(index)+" trong file excel", custom_message_box::Error).exec();
                return;
            }
            dkxt->ma_nganh = ma_nganh_opt.value();
            dkxt->thi_sinh = adding;
            dkxt->id_thi_sinh = adding->id;
            dkxt->id_ma_nganh = dkxt->ma_nganh->id;

            QSqlError err = qx::dao::insert(dkxt);
            if (err.isValid()){

            }

            ++index;
            progress_bar.setCurrentValue(index-3);
            QApplication::processEvents();
        }
        progress_bar.close();
    }
}



#endif // THI_SINH_DAO_H
