#ifndef PTXT_DAO_H
#define PTXT_DAO_H

#include "db/models/ptxt.h"
#include "utils/string.h"

// inline bool addPtxt(QString ma_nganh, QString ten_nganh, long id_nhom_nganh){
//     ptxt_ptr adding;
//     adding.reset(new nganh());
//     adding->ma_nganh = ma_nganh;
//     adding->ten_nganh = ten_nganh;
//     adding->nhom_nganh = std::make_shared<nhom_nganh>(id_nhom_nganh);

//     trimLeadingAndTrailing(adding->ma_nganh);
//     trimLeadingAndTrailing(adding->ten_nganh);

//     QSqlError err = qx::dao::insert(adding);
//     if (err.isValid())
//         return false;
//     else
//         return true;
// }

inline std::optional<QList<ptxt_ptr>> getAllPtxt(){
    QList<ptxt_ptr> list;

    QSqlError err = qx::dao::fetch_all(list);

    if (err.isValid()) {
        // qDebug() << "Error:" << err.text();
        return std::nullopt;
    } else {
        return list;
    }
}

inline std::optional<ptxt_ptr> getPtxtById(long &id){
    ptxt_ptr item = std::make_shared<ptxt>(id);
    QSqlError err = qx::dao::fetch_by_id(item);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return std::nullopt;
    } else {
        return item;
    }
}

inline bool deletePtxtById(long &id){
    auto item = getPtxtById(id);
    if (!item) return false;
    QSqlError err = qx::dao::delete_by_id(*item);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return false;
    } else {
        return true;
    }
}

#endif // PTXT_DAO_H
