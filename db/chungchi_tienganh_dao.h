#ifndef CHUNGCHI_TIENGANH_DAO_H
#define CHUNGCHI_TIENGANH_DAO_H

#include "db/models/chungchi_tienganh.h"
#include "utils/string.h"

inline bool addChungchiTienganh(long &id_thi_sinh, QString &loai_chungchi, float &diem,
                                QDate &ngay_cap, QDate &ngay_het_han){
    chungchi_tienganh_ptr adding;
    adding.reset(new chungchi_tienganh());
    adding->thi_sinh = std::make_shared<thi_sinh>(id_thi_sinh);
    adding->loai_chungchi = loai_chungchi;
    adding->diem = diem;
    adding->ngay_cap = ngay_cap;
    adding->ngay_het_han = ngay_het_han;

    trimLeadingAndTrailing(adding->loai_chungchi);

    QSqlError err = qx::dao::insert(adding);
    if (err.isValid())
        return false;
    else
        return true;
}

inline bool changeChungchiTienganh(chungchi_tienganh_ptr &item, QString &loai_chungchi,
                                   float &diem, QDate &ngay_cap, QDate &ngay_het_han){
    item->loai_chungchi = loai_chungchi;
    item->diem = diem;
    item->ngay_cap = ngay_cap;
    item->ngay_het_han = ngay_het_han;

    trimLeadingAndTrailing(item->loai_chungchi);

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
    query.where("id_thi_sinh").isEqualTo(QVariant::fromValue(id_thi_sinh));
    QSqlError err = qx::dao::fetch_by_query(query, list);
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
