#ifndef DIEM_HOCBA_DAO_H
#define DIEM_HOCBA_DAO_H

#include <QApplication>

#include "db/models/diem_hocba.h"
#include "db/monhoc_dao.h"
#include "ui/components/progressbar.h"
#include "excel/read_excel.h"

inline bool addDiemHocba(long &id_thi_sinh, long &id_mon_hoc, float &lop10,
                         float &lop11, float &lop12){
    diem_hocba_ptr adding;
    adding.reset(new diem_hocba());
    adding->thi_sinh = std::make_shared<thi_sinh>(id_thi_sinh);
    adding->mon_hoc = std::make_shared<mon_hoc>(id_mon_hoc);
    adding->lop10 = lop10;
    adding->lop11 = lop11;
    adding->lop12 = lop12;

    QSqlError err = qx::dao::insert(adding);
    if (err.isValid())
        return false;
    else
        return true;
}

inline bool changeDiemHocba(diem_hocba_ptr &item, long &id_mon_hoc, float &lop10, float &lop11, float &lop12){
    item->lop10 = lop10;
    item->lop11 = lop11;
    item->lop12 = lop12;
    item->mon_hoc = std::make_shared<mon_hoc>(id_mon_hoc);

    QSqlError err = qx::dao::update(item);
    if (err.isValid())
        return false;
    else
        return true;
}

inline std::optional<diem_hocba_ptr> getDiemHocbaById(long &id){
    diem_hocba_ptr item;
    item.reset(new diem_hocba(id));
    QSqlError err = qx::dao::fetch_by_id(item);
    if (err.isValid())
        return std::nullopt;
    else
        return item;
}

inline std::optional<QList<diem_hocba_ptr>> getDiemHocbaByThiSinhId(long &id_thi_sinh){
    QList<diem_hocba_ptr> list;
    qx_query query;
    query.where("diem_hocba.id_thi_sinh").isEqualTo(QVariant::fromValue(id_thi_sinh));
    QSqlError err = qx::dao::fetch_by_query_with_all_relation(query, list);
    if (err.isValid())
        return std::nullopt;
    else
        return list;
}

inline std::optional<QList<diem_hocba_ptr>> getAllDiemHocba(){
    QList<diem_hocba_ptr> list;
    qx_query query;
    query.orderAsc("diem_hocba.id_thi_sinh");
    QSqlError err = qx::dao::fetch_by_query_with_all_relation(query, list);
    if (err.isValid())
        return std::nullopt;
    else
        return list;
}

inline std::optional<diem_hocba_ptr> getDiemHocbaByThiSinhIdAndName(long &id_thi_sinh, long &id_monhoc){
    QList<diem_hocba_ptr> list;
    qx_query query;
    query.where("id_thi_sinh").isEqualTo(QVariant::fromValue(id_thi_sinh))
        .and_("id_monhoc").isEqualTo(QVariant::fromValue(id_monhoc));

    QSqlError err = qx::dao::fetch_by_query(query, list);
    if (err.isValid())
        return std::nullopt;
    else
        if (list.isEmpty()) return std::nullopt;
        return list.first();
}

inline bool deleteDiemHocbaById(long &id){
    diem_hocba_ptr item;
    item.reset(new diem_hocba(id));
    QSqlError err = qx::dao::delete_by_id(item);
    if (err.isValid())
        return false;
    else
        return true;
}

inline bool exportHocBaToExcel(QString &path){
    auto list_opt = getAllDiemHocba();
    auto list_mon_hoc_opt = getAllMonHoc();
    if (!list_opt || !list_mon_hoc_opt) return false;
    auto list = *list_opt;
    auto list_mon_hoc = list_mon_hoc_opt.value();

    QXlsx::Document xlsx;
    // Title
    int row = 1;
    xlsx.write(row, 1, "DANH SÁCH ĐIỂM HỌC BẠ CỦA THÍ SINH");
    xlsx.mergeCells("A1:L1");
    // Header
    ++row;
    xlsx.write(row, 1, "STT");
    xlsx.write(row, 2, "Số định danh");
    xlsx.write(row, 3, "Họ tên");
    xlsx.write(row, 4, "CMND/CCCD");
    xlsx.write(row, 5, "Ngày sinh");
    xlsx.write(row, 6, "Giới tính");
    xlsx.write(row, 7, "Lớp");
    for (int i = 0; i < list_mon_hoc.length(); i++){
        xlsx.write(row, 8+i, list_mon_hoc[i]->ten_monhoc);
    }

    long id = 0;
    QList<diem_hocba_ptr> hoc_ba_hold;
    progressBar progress_bar;
    progress_bar.setInitValue(list.length());
    progress_bar.show();
    int index = 0;
    for (auto &item : list){
        ++index;
        if (progress_bar.is_closed){
            return true;
        }

        if (id != item->thi_sinh->id){
            id = item->thi_sinh->id;
            if (!hoc_ba_hold.empty()) {
                for (int i = 1; i <= 3; ++i) {
                    xlsx.write(row+i, 1, row-2+i);
                    xlsx.write(row+i, 2, hoc_ba_hold[0]->thi_sinh->cccd);
                    xlsx.write(row+i, 3, hoc_ba_hold[0]->thi_sinh->ho_ten);
                    xlsx.write(row+i, 4, hoc_ba_hold[0]->thi_sinh->cccd);
                    xlsx.write(row+i, 5, hoc_ba_hold[0]->thi_sinh->ngay_sinh.toString("dd/MM/yyyy"));
                    xlsx.write(row+i, 6, hoc_ba_hold[0]->thi_sinh->gioi_tinh);
                    xlsx.write(row+i, 7, 9+i);
                }
                for (auto &hoc_ba : hoc_ba_hold){
                    int mon_hoc_index;
                    for (mon_hoc_index = 0; mon_hoc_index < list_mon_hoc.length(); mon_hoc_index++){
                        if (hoc_ba->mon_hoc->id_monhoc == list_mon_hoc[mon_hoc_index]->id_monhoc){
                            break;
                        }
                    }
                    xlsx.write(row+1, 8+mon_hoc_index, hoc_ba->lop10);
                    xlsx.write(row+2, 8+mon_hoc_index, hoc_ba->lop11);
                    xlsx.write(row+3, 8+mon_hoc_index, hoc_ba->lop12);
                }
                row += 3;
                hoc_ba_hold.clear();
                progress_bar.setCurrentValue(row-2);
            }
        }
        hoc_ba_hold.append(item);

        QApplication::processEvents();
    }
    if (!hoc_ba_hold.empty()){
        for (int i = 1; i <= 3; ++i) {
            xlsx.write(row+i, 1, row-2+i);
            xlsx.write(row+i, 2, hoc_ba_hold[0]->thi_sinh->cccd);
            xlsx.write(row+i, 3, hoc_ba_hold[0]->thi_sinh->ho_ten);
            xlsx.write(row+i, 4, hoc_ba_hold[0]->thi_sinh->cccd);
            xlsx.write(row+i, 5, hoc_ba_hold[0]->thi_sinh->ngay_sinh.toString("dd/MM/yyyy"));
            xlsx.write(row+i, 6, hoc_ba_hold[0]->thi_sinh->gioi_tinh);
            xlsx.write(row+i, 7, 9+i);
        }
        for (auto &hoc_ba : hoc_ba_hold){
            int mon_hoc_index;
            for (mon_hoc_index = 0; mon_hoc_index < list_mon_hoc.length(); mon_hoc_index++){
                if (hoc_ba->mon_hoc->id_monhoc == list_mon_hoc[mon_hoc_index]->id_monhoc){
                    break;
                }
            }
            xlsx.write(row+1, 8+mon_hoc_index, hoc_ba->lop10);
            xlsx.write(row+2, 8+mon_hoc_index, hoc_ba->lop11);
            xlsx.write(row+3, 8+mon_hoc_index, hoc_ba->lop12);
        }
        row += 3;
        hoc_ba_hold.clear();
        progress_bar.setCurrentValue(row-2);
    }

    progress_bar.close();

    return xlsx.saveAs(path);
}

#endif // DIEM_HOCBA_DAO_H
