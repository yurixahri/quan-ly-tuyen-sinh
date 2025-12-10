#ifndef DIEM_HOCBA_DAO_H
#define DIEM_HOCBA_DAO_H

#include "db/models/diem_hocba.h"

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
    query.where("id_thi_sinh").isEqualTo(QVariant::fromValue(id_thi_sinh));
    QSqlError err = qx::dao::fetch_by_query(query, list);
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

#endif // DIEM_HOCBA_DAO_H
