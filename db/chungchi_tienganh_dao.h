#ifndef CHUNGCHI_TIENGANH_DAO_H
#define CHUNGCHI_TIENGANH_DAO_H

#include "db/models/chungchi_tienganh.h"

inline bool addChungchiTienganh(long &id_thi_sinh, long &id_ccnn, float &diem, long &id_ptxt){
    chungchi_tienganh_ptr adding;
    adding.reset(new chungchi_tienganh());
    adding->thi_sinh = std::make_shared<thi_sinh>(id_thi_sinh);
    adding->ccnn = std::make_shared<ma_chungchinn>(id_ccnn);
    adding->ptxt = std::make_shared<ptxt>(id_ptxt);
    adding->diem = diem;

    QSqlError err = qx::dao::insert(adding);
    if (err.isValid())
        return false;
    else
        return true;
}

inline bool changeChungchiTienganh(chungchi_tienganh_ptr &item, long &id_ccnn, float &diem, long &id_ptxt){
    item->diem = diem;
    item->ccnn = std::make_shared<ma_chungchinn>(id_ccnn);
    item->ptxt = std::make_shared<ptxt>(id_ptxt);
    QSqlError err = qx::dao::update(item);
    if (err.isValid())
        return false;
    else
        return true;
}

inline std::optional<chungchi_tienganh_ptr> getChungchiTienganhById(long &id){
    chungchi_tienganh_ptr item;
    item.reset(new chungchi_tienganh(id));
    QSqlError err = qx::dao::fetch_by_id(item);
    if (err.isValid())
        return std::nullopt;
    else
        return item;
}

inline std::optional<QList<chungchi_tienganh_ptr>> getChungchiTienganhByThiSinhId(long &id_thi_sinh){
    QList<chungchi_tienganh_ptr> list;
    qx_query query;
    QStringList relations;
    relations.append("id_ptxt");
    relations.append("id_ccnn");
    query.where("chungchi_ngoaingu.id_thi_sinh").isEqualTo(QVariant::fromValue(id_thi_sinh));
    QSqlError err = qx::dao::fetch_by_query_with_all_relation(query, list);
    if (err.isValid())
        return std::nullopt;
    else
        return list;
}

inline bool deleteChungchiTienganhById(long &id){
    chungchi_tienganh_ptr item;
    item.reset(new chungchi_tienganh(id));
    QSqlError err = qx::dao::delete_by_id(item);
    if (err.isValid())
        return false;
    else
        return true;
}

#endif // CHUNGCHI_TIENGANH_DAO_H
