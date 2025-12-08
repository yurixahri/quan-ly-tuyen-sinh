#ifndef DIEM_THI_SAT_DAO_H
#define DIEM_THI_SAT_DAO_H

#include "db/models/diem_thi_sat.h"

inline bool addDiemThiSat(long &id_thi_sinh, float &reading, float &writing,
                          float &math, float &total){
    diem_thi_sat_ptr adding;
    adding.reset(new diem_thi_sat());
    adding->thi_sinh = std::make_shared<thi_sinh>(id_thi_sinh);
    adding->reading = reading;
    adding->writing = writing;
    adding->math = math;
    adding->total = total;

    QSqlError err = qx::dao::insert(adding);
    if (err.isValid())
        return false;
    else
        return true;
}

inline bool changeDiemThiSat(diem_thi_sat_ptr &item, float &reading, float &writing,
                             float &math, float &total){
    item->reading = reading;
    item->writing = writing;
    item->math = math;
    item->total = total;

    QSqlError err = qx::dao::update(item);
    if (err.isValid())
        return false;
    else
        return true;
}

inline std::optional<diem_thi_sat_ptr> getDiemThiSatById(long &id){
    diem_thi_sat_ptr item;
    item.reset(new diem_thi_sat(id));
    QSqlError err = qx::dao::fetch_by_id(item);
    if (err.isValid())
        return std::nullopt;
    else
        return item;
}

inline std::optional<diem_thi_sat_ptr> getDiemThiSatByThiSinhId(long &id_thi_sinh){
    QList<diem_thi_sat_ptr> list;
    qx_query query;
    query.where("id_thi_sinh").isEqualTo(QVariant::fromValue(id_thi_sinh));
    QSqlError err = qx::dao::fetch_by_query(query, list);
    if (err.isValid())
        return std::nullopt;
    else
        return list.isEmpty() ? std::nullopt : std::make_optional(list.first());
}

inline bool deleteDiemThiSatById(long &id){
    diem_thi_sat_ptr item;
    item.reset(new diem_thi_sat(id));
    QSqlError err = qx::dao::delete_by_id(item);
    if (err.isValid())
        return false;
    else
        return true;
}
#endif // DIEM_THI_SAT_DAO_H
