#ifndef DOAT_GIAI_DAO_H
#define DOAT_GIAI_DAO_H

#include "db/models/doat_giai.h"
#include "utils/string.h"

inline bool addDoatGiai(long &id_thi_sinh, long &id_monhoc, long &id_ptxt,
                        QString &thanh_tich, int &diem_thanh_tich){
    doat_giai_ptr adding;
    adding.reset(new doat_giai());
    adding->thi_sinh = std::make_shared<thi_sinh>(id_thi_sinh);
    adding->mon_hoc = std::make_shared<mon_hoc>(id_monhoc);
    adding->ptxt = std::make_shared<ptxt>(id_ptxt);
    adding->thanh_tich = thanh_tich;
    adding->diem_thanh_tich = diem_thanh_tich;

    trimLeadingAndTrailing(adding->thanh_tich);

    QSqlError err = qx::dao::insert(adding);
    if (err.isValid())
        return false;
    else
        return true;
}

inline bool changeDoatGiai(doat_giai_ptr &item, long &id_monhoc, long &id_ptxt, QString &thanh_tich, int &diem_thanh_tich){
    item->thanh_tich = thanh_tich;
    item->diem_thanh_tich = diem_thanh_tich;
    item->mon_hoc = std::make_shared<mon_hoc>(id_monhoc);
    item->ptxt = std::make_shared<ptxt>(id_ptxt);

    trimLeadingAndTrailing(item->thanh_tich);

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
    query.where("id_thi_sinh").isEqualTo(QVariant::fromValue(id_thi_sinh));
    QSqlError err = qx::dao::fetch_by_query(query, list);
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

#endif // DOAT_GIAI_DAO_H
