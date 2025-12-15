#ifndef MA_DTUT_DAO_H
#define MA_DTUT_DAO_H

#include "db/models/ma_dtut.h"
#include "utils/string.h"

inline bool addMaDtut(QString &ma, QString &ten, float &diem){
    ma_dtut_ptr adding;
    adding.reset(new ma_dtut());
    adding->ma = ma;
    adding->ten = ten;
    adding->diem = diem;

    trimLeadingAndTrailing(adding->ma);
    trimLeadingAndTrailing(adding->ten);

    if (adding->ma.isEmpty())
        return false;

    QSqlError err = qx::dao::insert(adding);
    if (err.isValid())
        return false;
    else
        return true;
}

inline bool changeMaDtut(ma_dtut_ptr &item, QString &ma, QString &ten, float &diem){
    item->ma = ma;
    item->ten = ten;
    item->diem = diem;

    trimLeadingAndTrailing(item->ma);
    trimLeadingAndTrailing(item->ten);

    if (item->ma.isEmpty())
        return false;

    QSqlError err = qx::dao::update(item);
    if (err.isValid())
        return false;
    else
        return true;
}

inline std::optional<QList<ma_dtut_ptr>> getAllMaDtut(){
    QList<ma_dtut_ptr> list;
    QSqlError err = qx::dao::fetch_all(list);
    if (err.isValid())
        return std::nullopt;
    else
        return list;
}

inline std::optional<ma_dtut_ptr> getMaDtutById(long &id){
    ma_dtut_ptr item;
    item.reset(new ma_dtut(id));
    QSqlError err = qx::dao::fetch_by_id(item);
    if (err.isValid())
        return std::nullopt;
    else
        return item;
}

inline std::optional<ma_dtut_ptr> getMaDtutByName(QString &name){
    QList<ma_dtut_ptr> list;
    qx_query query;
    query.where("ma").isEqualTo(QVariant::fromValue(name));
    QSqlError err = qx::dao::fetch_by_query(query, list);

    if (err.isValid()) {
        return std::nullopt;
    } else {
        if (list.isEmpty()) return std::nullopt;
        return list.first();
    }
}

inline bool deleteMaDtutById(long &id){
    ma_dtut_ptr item;
    item.reset(new ma_dtut(id));
    QSqlError err = qx::dao::delete_by_id(item);
    if (err.isValid())
        return false;
    else
        return true;
}

#endif // MA_DTUT_DAO_H
