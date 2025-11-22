#ifndef NGANH_DAO_H
#define NGANH_DAO_H

#include "db/models/nganh.h"
#include "utils/string.h"

inline bool addNganh(QString ma_nganh, QString ten_nganh, long id_nhom_nganh){
    nganh_ptr adding;
    adding.reset(new nganh());
    adding->ma_nganh = ma_nganh;
    adding->ten_nganh = ten_nganh;
    adding->nhom_nganh = std::make_shared<nhom_nganh>(id_nhom_nganh);

    trimLeadingAndTrailing(adding->ma_nganh);
    trimLeadingAndTrailing(adding->ten_nganh);

    QSqlError err = qx::dao::insert(adding);
    if (err.isValid())
        return false;
    else
        return true;
}

inline std::optional<QList<nganh_ptr>> getAllNganh(){
    QList<nganh_ptr> list;

    QSqlError err = qx::dao::fetch_all_with_all_relation(list);

    if (err.isValid()) {
        // qDebug() << "Error:" << err.text();
        return std::nullopt;
    } else {
        return list;
    }
}

inline std::optional<nganh_ptr> getNganhById(long &id){
    nganh_ptr item = std::make_shared<nganh>(id);
    QSqlError err = qx::dao::fetch_by_id(item);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return std::nullopt;
    } else {
        return item;
    }
}

inline bool deleteNganhById(long &id){
    auto item = getNganhById(id);
    if (!item) return false;
    QSqlError err = qx::dao::delete_by_id(*item);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return false;
    } else {
        return true;
    }
}

#endif // NGANH_DAO_H
