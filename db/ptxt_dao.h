#ifndef PTXT_DAO_H
#define PTXT_DAO_H

#include "db/models/ptxt.h"
#include "utils/string.h"

inline bool addPtxt(QString ma, QString ten, float thang_diem, QString mo_ta){
    ptxt_ptr adding;
    adding.reset(new ptxt());
    adding->ma = ma;
    adding->ten = ten;
    adding->thang_diem = thang_diem;
    adding->mo_ta = mo_ta;

    trimLeadingAndTrailing(adding->ma);
    trimLeadingAndTrailing(adding->ten);

    QSqlError err = qx::dao::insert(adding);
    if (err.isValid())
        return false;
    else
        return true;
}

inline bool changePtxt(ptxt_ptr item, QString ma, QString ten, float thang_diem, QString mo_ta){
    item->ma = ma;
    item->ten = ten;
    item->thang_diem = thang_diem;
    item->mo_ta = mo_ta;

    trimLeadingAndTrailing(item->ma);
    trimLeadingAndTrailing(item->ten);

    QSqlError err = qx::dao::update(item);
    if (err.isValid())
        return false;
    else
        return true;
}

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

inline bool deleteAllPtxt(){
    qx::QxSession session;
    session += qx::dao::delete_all<ptxt>(session.database());

    if (!session.isValid()) {
        return false;
    } else {
        return true;
    }
}

#endif // PTXT_DAO_H
