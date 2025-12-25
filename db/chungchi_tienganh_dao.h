#ifndef CHUNGCHI_TIENGANH_DAO_H
#define CHUNGCHI_TIENGANH_DAO_H

#include "db/models/chungchi_tienganh.h"
#include "excel/read_excel.h"

inline bool addChungchiTienganh(long &id_thi_sinh, long &id_ccnn, float &diem, long &id_ptxt){
    chungchi_tienganh_ptr adding;
    adding.reset(new chungchi_tienganh());
    adding->thi_sinh = std::make_shared<thi_sinh>(id_thi_sinh);
    adding->ccnn = std::make_shared<ma_chungchinn>(id_ccnn);
    adding->ptxt = std::make_shared<ptxt>(id_ptxt);
    adding->diem = diem;

    QSqlError err = qx::dao::insert(adding);
    if (err.isValid())
        return false;
    else
        return true;
}

inline bool changeChungchiTienganh(chungchi_tienganh_ptr &item, long &id_ccnn, float &diem, long &id_ptxt){
    item->diem = diem;
    item->ccnn = std::make_shared<ma_chungchinn>(id_ccnn);
    if (id_ptxt)
        item->ptxt = std::make_shared<ptxt>(id_ptxt);
    else
        item->ptxt = NULL;
    QSqlError err = qx::dao::update(item);
    if (err.isValid())
        return false;
    else
        return true;
}

inline std::optional<chungchi_tienganh_ptr> getChungchiTienganhById(long &id){
    chungchi_tienganh_ptr item;
    item.reset(new chungchi_tienganh(id));
    QSqlError err = qx::dao::fetch_by_id(item);
    if (err.isValid())
        return std::nullopt;
    else
        return item;
}

inline std::optional<QList<chungchi_tienganh_ptr>> getChungchiTienganhByThiSinhId(long &id_thi_sinh){
    QList<chungchi_tienganh_ptr> list;
    qx_query query;
    QStringList relations;
    relations.append("id_ptxt");
    relations.append("id_ccnn");
    query.where("chungchi_ngoaingu.id_thi_sinh").isEqualTo(QVariant::fromValue(id_thi_sinh));
    QSqlError err = qx::dao::fetch_by_query_with_all_relation(query, list);
    if (err.isValid())
        return std::nullopt;
    else
        return list;
}

inline std::optional<QList<chungchi_tienganh_ptr>> getAllCCNN(){
    QList<chungchi_tienganh_ptr> list;
    QSqlError err = qx::dao::fetch_all_with_all_relation(list);
    if (err.isValid())
        return std::nullopt;
    else
        return list;
}

inline bool deleteChungchiTienganhById(long &id){
    chungchi_tienganh_ptr item;
    item.reset(new chungchi_tienganh(id));
    QSqlError err = qx::dao::delete_by_id(item);
    if (err.isValid())
        return false;
    else
        return true;
}

inline bool exportCCNNToExcel(QString &path){
    auto list_opt = getAllCCNN();
    if (!list_opt) return false;
    auto list = *list_opt;

    QXlsx::Document xlsx;
    // Title
    int row = 1;
    xlsx.write(row, 1, "DANH SÁCH CCNN CỦA THÍ SINH");
    xlsx.mergeCells("A1:L1");
    // Header
    ++row;
    xlsx.write(row, 1, "STT");
    xlsx.write(row, 2, "Số báo danh");
    xlsx.write(row, 3, "CMND/CCCD");
    xlsx.write(row, 4, "Tên hứng chỉ");
    xlsx.write(row, 5, "Điểm / Bậc chứng chỉ");
    xlsx.write(row, 6, "Mã chứng chỉ");
    xlsx.write(row, 7, "Thành tích");
    xlsx.write(row, 8, "Môn đạt giải");
    xlsx.write(row, 9, "Điểm cộng");
    xlsx.write(row, 10, "PTXT");

    for (auto &item : list){
        ++row;

        xlsx.write(row, 1, row-2);
        xlsx.write(row, 2, item->thi_sinh->sbd);
        xlsx.write(row, 3, item->thi_sinh->cccd);
        xlsx.write(row, 4, item->ccnn ? item->ccnn->ten : "");
        xlsx.write(row, 5, item->diem);
        xlsx.write(row, 6, item->ccnn ? item->ccnn->ma : "");
        xlsx.write(row, 10, item->ptxt ? item->ptxt->ma : "");
    }

    return xlsx.saveAs(path);
}

#endif // CHUNGCHI_TIENGANH_DAO_H
