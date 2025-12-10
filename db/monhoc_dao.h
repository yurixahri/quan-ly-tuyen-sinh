#ifndef MONHOC_DAO_H
#define MONHOC_DAO_H

#include "db/models/mon_hoc.h"

inline bool addMonHoc(QString &ten){
    mon_hoc_ptr adding;
    adding.reset(new mon_hoc());
    adding->ten_monhoc = ten;

    QSqlError err = qx::dao::insert(adding);
    if (err.isValid())
        return false;
    else
        return true;
}

inline std::optional<QList<mon_hoc_ptr>> getAllMonHoc(){
    QList<mon_hoc_ptr> list;

    QSqlError err = qx::dao::fetch_all(list);

    if (err.isValid()) {
        // qDebug() << "Error:" << err.text();
        return std::nullopt;
    } else {
        return list;
    }
}

inline std::optional<mon_hoc_ptr> getMonHocById(long &id){
    mon_hoc_ptr item = std::make_shared<mon_hoc>(id);
    QSqlError err = qx::dao::fetch_by_id(item);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return std::nullopt;
    } else {
        return item;
    }
}

inline std::optional<mon_hoc_ptr> getMonHocByName(QString &name){
    QList<mon_hoc_ptr> list;
    qx_query query("where ten_monhoc ilike :name");
    query.bind(":name", "%"+name+"%");
    QSqlError err = qx::dao::fetch_by_query(query, list);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return std::nullopt;
    } else {
        if (list.isEmpty()) return std::nullopt;
        return list.first();
    }
}

inline bool deleteMonHocById(long &id){
    auto item = getMonHocById(id);
    if (!item) return false;
    QSqlError err = qx::dao::delete_by_id(*item);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return false;
    } else {
        return true;
    }
}

inline bool deleteAllMonHoc(){
    qx::QxSession session;
    session += qx::dao::delete_all<mon_hoc>(session.database());

    if (!session.isValid()) {
        return false;
    } else {
        return true;
    }
}

#endif // MONHOC_DAO_H
