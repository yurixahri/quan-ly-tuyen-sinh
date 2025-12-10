#ifndef MA_CHUNGCHINN_DAO_H
#define MA_CHUNGCHINN_DAO_H

#include "db/models/ma_chungchinn.h"
#include "utils/string.h"

inline bool addMaChungchinn(QString &ma, QString &ten){
    ma_chungchinn_ptr adding;
    adding.reset(new ma_chungchinn());
    adding->ma = ma;
    adding->ten = ten;

    trimLeadingAndTrailing(adding->ma);
    trimLeadingAndTrailing(adding->ten);

    if (adding->ma.isEmpty() || adding->ten.isEmpty())
        return false;

    QSqlError err = qx::dao::insert(adding);
    if (err.isValid())
        return false;
    else
        return true;
}

inline bool changeMaChungchinn(ma_chungchinn_ptr &item, QString &ma, QString &ten){
    item->ma = ma;
    item->ten = ten;

    trimLeadingAndTrailing(item->ma);
    trimLeadingAndTrailing(item->ten);

    if (item->ma.isEmpty() || item->ten.isEmpty())
        return false;

    QSqlError err = qx::dao::update(item);
    if (err.isValid())
        return false;
    else
        return true;
}

inline std::optional<QList<ma_chungchinn_ptr>> getAllMaChungchinn(){
    QList<ma_chungchinn_ptr> list;
    QSqlError err = qx::dao::fetch_all(list);
    if (err.isValid())
        return std::nullopt;
    else
        return list;
}

inline std::optional<ma_chungchinn_ptr> getMaChungchinnById(long &id){
    ma_chungchinn_ptr item;
    item.reset(new ma_chungchinn(id));
    QSqlError err = qx::dao::fetch_by_id(item);
    if (err.isValid())
        return std::nullopt;
    else
        return item;
}

inline std::optional<ma_chungchinn_ptr> getMaChungchinnName(QString &name){
    QList<ma_chungchinn_ptr> list;
    qx_query query;
    query.where("ten_ccnn").isEqualTo(QVariant::fromValue(name));
    QSqlError err = qx::dao::fetch_by_query(query, list);

    if (err.isValid()) {
        return std::nullopt;
    } else {
        if (list.isEmpty()) return std::nullopt;
        return list.first();
    }
}

inline bool deleteMaChungchinnById(long &id){
    ma_chungchinn_ptr item;
    item.reset(new ma_chungchinn(id));
    QSqlError err = qx::dao::delete_by_id(item);
    if (err.isValid())
        return false;
    else
        return true;
}

#endif // MA_CHUNGCHINN_DAO_H
