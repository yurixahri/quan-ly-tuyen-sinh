#ifndef TOHOP_DAO_H
#define TOHOP_DAO_H

#include "db/models/to_hop_mon.h"

inline bool addToHop(QString ma_tohop, long id_mon_1, long id_mon_2, long id_mon_3){
    tohop_mon_ptr tohop_adding;
    tohop_adding.reset(new to_hop_mon());
    tohop_adding->ma_tohop = ma_tohop;
    tohop_adding->mon_1 = std::make_shared<mon_hoc>(id_mon_1);
    tohop_adding->mon_2 = std::make_shared<mon_hoc>(id_mon_2);
    tohop_adding->mon_3 = std::make_shared<mon_hoc>(id_mon_3);

    QSqlError err = qx::dao::insert(tohop_adding);
    if (err.isValid()){
        qDebug() << "Error:" << err.text();
        return false;
    }else
        return true;
}

inline std::optional<QList<tohop_mon_ptr>> getAllToHop(){
    QList<tohop_mon_ptr> list;

    QSqlError err = qx::dao::fetch_all_with_all_relation(list);

    if (err.isValid()) {
        // qDebug() << "Error:" << err.text();
        return std::nullopt;
    } else {
        return list;
    }
}

inline std::optional<tohop_mon_ptr> getToHopById(long &id){
    tohop_mon_ptr item = std::make_shared<to_hop_mon>(id);
    QSqlError err = qx::dao::fetch_by_id(item);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return std::nullopt;
    } else {
        return item;
    }
}

inline bool deleteToHopById(long &id){
    auto item = getToHopById(id);
    if (!item) return false;
    QSqlError err = qx::dao::delete_by_id(*item);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return false;
    } else {
        return true;
    }
}

#endif // TOHOP_DAO_H
