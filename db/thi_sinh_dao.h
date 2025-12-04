#ifndef THI_SINH_DAO_H
#define THI_SINH_DAO_H

#include "db/models/thi_sinh.h"
#include "utils/string.h"

uint16_t page = 0;
uint16_t count = 100;

inline bool addThiSinh(QString cccd, QString ho_ten,
                       QDate ngay_sinh, QString gioi_tinh,
                       QString dia_chi, QString email, QString sdt, QString ma_dinh_danh ){
    thi_sinh_ptr adding;
    adding.reset(new thi_sinh());
    adding->cccd = cccd;
    adding->ho_ten = ho_ten;
    adding->ngay_sinh = ngay_sinh;
    adding->gioi_tinh = gioi_tinh;
    adding->dia_chi = dia_chi;
    adding->email = email;
    adding->sdt = sdt;
    adding->ma_dinh_danh = ma_dinh_danh;

    trimLeadingAndTrailing(adding->cccd);
    trimLeadingAndTrailing(adding->ho_ten);
    trimLeadingAndTrailing(adding->sdt);
    trimLeadingAndTrailing(adding->ma_dinh_danh);

    if (!isPhoneNumberValid(adding->sdt)) return false;

    QSqlError err = qx::dao::insert(adding);
    if (err.isValid())
        return false;
    else
        return true;
}

inline bool changeThiSinh(thi_sinh_ptr item, QString ma, QString ten, QString mo_ta){
    /*item->ma = ma;
    item->ten = ten;
    item->mo_ta = mo_ta;

    trimLeadingAndTrailing(item->ma);
    trimLeadingAndTrailing(item->ten);

    QSqlError err = qx::dao::update(item);
    if (err.isValid())
        return false;
    else
        return true*/;
}

inline std::optional<QList<thi_sinh_ptr>> getAllThiSinh(){
    QList<thi_sinh_ptr> list;

    qx_query query;
    query.limit(count, page*count);
    QSqlError err = qx::dao::fetch_by_query(query, list);

    if (err.isValid()) {
        // qDebug() << "Error:" << err.text();
        return std::nullopt;
    } else {
        return list;
    }
}

inline std::optional<thi_sinh_ptr> getThiSinhById(long &id){
    thi_sinh_ptr item = std::make_shared<thi_sinh>(id);
    QSqlError err = qx::dao::fetch_by_id(item);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return std::nullopt;
    } else {
        return item;
    }
}

inline bool deleteThiSinhById(long &id){
    auto item = getThiSinhById(id);
    if (!item) return false;
    QSqlError err = qx::dao::delete_by_id(*item);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return false;
    } else {
        return true;
    }
}

#endif // THI_SINH_DAO_H
