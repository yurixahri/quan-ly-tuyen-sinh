#ifndef MONHOC_DAO_H
#define MONHOC_DAO_H

#include "db/models/mon_hoc.h"

typedef std::shared_ptr<mon_hoc> mon_hoc_ptr;

bool addMonHoc(QString ma_monhoc, QString ten_monhoc){
    mon_hoc_ptr monhoc_adding;
    monhoc_adding.reset(new mon_hoc());
    monhoc_adding->ma_monhoc = ma_monhoc;
    monhoc_adding->ten_monhoc = ten_monhoc;

    QSqlError err = qx::dao::insert(monhoc_adding);
    if (err.isValid())
        return false;
    else
        return true;
}

std::optional<QList<mon_hoc_ptr>> getAllMonHoc(){
    QList<mon_hoc_ptr> list;

    QSqlError err = qx::dao::fetch_all(list);

    if (err.isValid()) {
        // qDebug() << "Error:" << err.text();
        return std::nullopt;
    } else {
        return list;
    }
}

#endif // MONHOC_DAO_H
