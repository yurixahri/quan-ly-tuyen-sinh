#ifndef NHOM_NGANH_DAO_H
#define NHOM_NGANH_DAO_H

#include "db/models/nhom_nganh.h"

inline bool addNhomNganh(QString &ten){
    nhom_nganh_ptr adding;
    adding.reset(new nhom_nganh());
    adding->ten = ten;

    QSqlError err = qx::dao::insert(adding);
    if (err.isValid()){
        return false;
    }
    else
        return true;
}

inline std::optional<QList<nhom_nganh_ptr>> getAllNhomNganh(){
    for (auto & name : *qx::QxClassX::getAllClasses())
        qDebug() << "Registered:" << name.first;
    QList<nhom_nganh_ptr> list;

    QSqlError err = qx::dao::fetch_all(list);

    if (err.isValid()) {
        // qDebug() << "Error:" << err.text();
        return std::nullopt;
    } else {
        return list;
    }
}

inline std::optional<nhom_nganh_ptr> getNhomNganhById(long &id){
    nhom_nganh_ptr item = std::make_shared<nhom_nganh>(id);
    QSqlError err = qx::dao::fetch_by_id(item);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return std::nullopt;
    } else {
        return item;
    }
}

inline bool deleteNhomNganhById(long &id){
    auto item = getNhomNganhById(id);
    if (!item) return false;
    QSqlError err = qx::dao::delete_by_id(*item);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return false;
    } else {
        return true;
    }
}

#endif // NHOM_NGANH_DAO_H
