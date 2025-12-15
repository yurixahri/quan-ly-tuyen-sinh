#ifndef MA_THANHTICH_DAO_H
#define MA_THANHTICH_DAO_H

#include "db/models/ma_thanhtich.h"
#include "utils/string.h"
#include <optional>

inline bool addMaThanhTich(QString &ma, QString &ten, float &diem){
    if (ma.isEmpty()) return false;
    ma_thanhtich_ptr adding(new ma_thanhtich());
    adding->ma = ma;
    adding->ten = ten;
    adding->diem = diem;

    trimLeadingAndTrailing(adding->ma);
    trimLeadingAndTrailing(adding->ten);



    QSqlError err = qx::dao::insert(adding);
    return !err.isValid();
}

inline bool changeMaThanhTich(ma_thanhtich_ptr &item, QString &ma, QString &ten, float &diem){
    if (ma.isEmpty()) return false;
    if (!item) return false;

    item->ma = ma;
    item->ten = ten;
    item->diem = diem;
    trimLeadingAndTrailing(item->ma);
    trimLeadingAndTrailing(item->ten);

    QSqlError err = qx::dao::update(item);
    return !err.isValid();
}

inline std::optional<ma_thanhtich_ptr> getMaThanhTichById(long &id){
    ma_thanhtich_ptr item(new ma_thanhtich(id));
    QSqlError err = qx::dao::fetch_by_id(item);
    if (err.isValid()) return std::nullopt;
    return item;
}

inline std::optional<ma_thanhtich_ptr> getMaThanhTichByName(QString &name){
    QList<ma_thanhtich_ptr> list;
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

inline std::optional<QList<ma_thanhtich_ptr>> getAllMaThanhTich(){
    QList<ma_thanhtich_ptr> list;
    QSqlError err = qx::dao::fetch_all(list);
    if (err.isValid()) return std::nullopt;
    return list;
}

inline bool deleteMaThanhTichById(long &id){
    ma_thanhtich_ptr item(new ma_thanhtich(id));
    QSqlError err = qx::dao::delete_by_id(item);
    return !err.isValid();
}

#endif // MA_THANHTICH_DAO_H
