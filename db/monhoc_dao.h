#ifndef MONHOC_DAO_H
#define MONHOC_DAO_H

#include "db/models/mon_hoc.h"

inline bool addMonHoc(QString ten_monhoc){
    mon_hoc_ptr monhoc_adding;
    monhoc_adding.reset(new mon_hoc());
    monhoc_adding->ten_monhoc = ten_monhoc;

    QSqlError err = qx::dao::insert(monhoc_adding);
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
    mon_hoc_ptr mon = std::make_shared<mon_hoc>(id);
    QSqlError err = qx::dao::fetch_by_id(mon);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return std::nullopt;
    } else {
        return mon;
    }
}

inline bool deleteMonHocById(long &id){
    auto mon = getMonHocById(id);
    if (!mon) return false;
    QSqlError err = qx::dao::delete_by_id(*mon);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return false;
    } else {
        return true;
    }
}

#endif // MONHOC_DAO_H
