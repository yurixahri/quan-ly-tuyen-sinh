#ifndef DOAT_GIAI_DAO_H
#define DOAT_GIAI_DAO_H

#include "db/models/doat_giai.h"
#include "db/models/ma_thanhtich.h"
#include "utils/string.h"
#include "excel/read_excel.h"

inline bool addDoatGiai(long &id_thi_sinh, long &id_monhoc, long &id_ptxt,
                        long &id_thanh_tich, int &diem_thanh_tich){
    doat_giai_ptr adding;
    adding.reset(new doat_giai());
    adding->thi_sinh = std::make_shared<thi_sinh>(id_thi_sinh);
    adding->mon_hoc = std::make_shared<mon_hoc>(id_monhoc);
    adding->ptxt = std::make_shared<ptxt>(id_ptxt);
    adding->thanh_tich = std::make_shared<ma_thanhtich>(id_thanh_tich);
    adding->diem_thanh_tich = diem_thanh_tich;

    QSqlError err = qx::dao::insert(adding);
    if (err.isValid())
        return false;
    else
        return true;
}

inline bool changeDoatGiai(doat_giai_ptr &item, long &id_monhoc, long &id_ptxt, long &id_thanh_tich, int &diem_thanh_tich){
    item->diem_thanh_tich = diem_thanh_tich;
    item->mon_hoc = std::make_shared<mon_hoc>(id_monhoc);
    item->thanh_tich = std::make_shared<ma_thanhtich>(id_thanh_tich);
    item->ptxt = std::make_shared<ptxt>(id_ptxt);

    QSqlError err = qx::dao::update(item);
    if (err.isValid())
        return false;
    else
        return true;
}

inline std::optional<doat_giai_ptr> getDoatGiaiById(long &id){
    doat_giai_ptr item;
    item.reset(new doat_giai());
    item->id = id;
    QSqlError err = qx::dao::fetch_by_id(item);
    if (err.isValid())
        return std::nullopt;
    else
        return item;
}

inline std::optional<QList<doat_giai_ptr>> getDoatGiaiByThiSinhId(long &id_thi_sinh){
    QList<doat_giai_ptr> list;
    qx_query query;
    query.where("doat_giai.id_thi_sinh").isEqualTo(QVariant::fromValue(id_thi_sinh));
    QSqlError err = qx::dao::fetch_by_query_with_all_relation(query, list);
    if (err.isValid())
        return std::nullopt;
    else
        return list;
}

inline std::optional<QList<doat_giai_ptr>> getAllDoatGiai(){
    QList<doat_giai_ptr> list;
    QSqlError err = qx::dao::fetch_all_with_relation("*->*",list);
    if (err.isValid())
        return std::nullopt;
    else
        return list;
}

inline bool deleteDoatGiaiById(long &id){
    doat_giai_ptr item;
    item.reset(new doat_giai());
    item->id = id;
    QSqlError err = qx::dao::delete_by_id(item);
    if (err.isValid())
        return false;
    else
        return true;
}

inline bool exportDoatGiaiToExcel(QString &path){
    auto list_opt = getAllDoatGiai();
    if (!list_opt) return false;
    auto list = *list_opt;

    QXlsx::Document xlsx;
    // Title
    int row = 1;
    xlsx.write(row, 1, "DANH SÁCH ĐOẠT GIẢI CỦA THÍ SINH");
    xlsx.mergeCells("A1:L1");
    // Header
    ++row;
    xlsx.write(row, 1, "STT");
    xlsx.write(row, 2, "Họ đệm");
    xlsx.write(row, 3, "Tên");
    xlsx.write(row, 4, "Giới tính");
    xlsx.write(row, 5, "CMND/CCCD");
    xlsx.write(row, 6, "Thành tích");
    xlsx.write(row, 7, "Môn đạt giải");
    xlsx.write(row, 8, "Điểm thành tích");
    xlsx.write(row, 9, "PTXT");

    for (auto &item : list){
        ++row;
        auto ho_ten = item->thi_sinh->ho_ten.split(" ");
        QString ten = ho_ten.last();
        ho_ten.pop_back();
        QString ho = ho_ten.join(" ");
        xlsx.write(row, 1, row-2);
        xlsx.write(row, 2, ho);
        xlsx.write(row, 3, ten);
        xlsx.write(row, 4, item->thi_sinh->gioi_tinh);
        xlsx.write(row, 5, item->thi_sinh->cccd);
        xlsx.write(row, 6, item->thanh_tich ? item->thanh_tich->ma : "");
        xlsx.write(row, 7, item->mon_hoc ? item->mon_hoc->ten_monhoc : "");
        xlsx.write(row, 8, item->diem_thanh_tich);
        xlsx.write(row, 9, item->ptxt ? item->ptxt->ma : "");
    }

    return xlsx.saveAs(path);
}

#endif // DOAT_GIAI_DAO_H
