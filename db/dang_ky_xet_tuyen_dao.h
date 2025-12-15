#ifndef DANG_KY_XET_TUYEN_DAO_H
#define DANG_KY_XET_TUYEN_DAO_H

#include "db/models/dang_ky_xet_tuyen.h"
#include "utils/string.h"
#include <optional>

inline bool addDangKyXetTuyen(long &id_thi_sinh, long &id_ma_nganh, long &id_ptxt, float &diem, QString &trang_thai) {
    dang_ky_xet_tuyen_ptr adding(new dang_ky_xet_tuyen());

    adding->id_thi_sinh = id_thi_sinh;
    adding->id_ma_nganh = id_ma_nganh;

    adding->thi_sinh = std::make_shared<thi_sinh>(id_thi_sinh);
    adding->ma_nganh = std::make_shared<ma_nganh>(id_ma_nganh);
    if (id_ptxt > 0) adding->ptxt = std::make_shared<ptxt>(id_ptxt);

    adding->diem = diem;
    adding->trang_thai = trang_thai.trimmed();

    QSqlError err = qx::dao::insert(adding);
    if (err.isValid())
        return false;
    else
        return true;
}

inline bool changeDangKyXetTuyen(dang_ky_xet_tuyen_ptr &item, long &id_ptxt, float &diem, QString &trang_thai) {
    if (!item) return false;
    item->diem = diem;
    item->trang_thai = trang_thai.trimmed();
    if (id_ptxt > 0) item->ptxt = std::make_shared<ptxt>(id_ptxt);
    qx_query query(R"sql(
        UPDATE dang_ky_xet_tuyen
        SET diem_xt = :diem_xt,
            trang_thai = :trang_thai,
            id_ptxt = :id_ptxt
        WHERE id_thi_sinh = :orig_id_thi_sinh
          AND id_ma_nganh = :orig_id_ma_nganh
    )sql");

    query.bind(":diem_xt", diem);
    query.bind(":trang_thai", trang_thai.trimmed());
    if (id_ptxt > 0) query.bind(":id_ptxt", QVariant::fromValue(id_ptxt));
    else  query.bind(":id_ptxt", QVariant(QVariant::Int)); // NULL
    query.bind(":orig_id_thi_sinh", QVariant::fromValue(item->id_thi_sinh));
    query.bind(":orig_id_ma_nganh", QVariant::fromValue(item->id_ma_nganh));

    QSqlError err = qx::dao::execute_query(query, item);
    if (err.isValid())
        return false;
    else
        return true;
}

inline std::optional<dang_ky_xet_tuyen_ptr> getDangKyByIds(long &id_thi_sinh, long &id_ma_nganh) {
    dang_ky_xet_tuyen_ptr item(new dang_ky_xet_tuyen());
    item->id_thi_sinh = id_thi_sinh;
    item->id_ma_nganh = id_ma_nganh;
    QSqlError err = qx::dao::fetch_by_id_with_relation("*->*", item);
    if (err.isValid()) return std::nullopt;
    return item;
}

inline std::optional<QList<dang_ky_xet_tuyen_ptr>> getDangKyByThiSinhId(long &id_thi_sinh) {
    QList<dang_ky_xet_tuyen_ptr> list;
    qx_query query;
    query.where("dang_ky_xet_tuyen.id_thi_sinh").isEqualTo(QVariant::fromValue(id_thi_sinh));
    QSqlError err = qx::dao::fetch_by_query_with_relation("*->*", query, list);
    if (err.isValid()) return std::nullopt;
    return list;
}


inline std::optional<QList<dang_ky_xet_tuyen_ptr>> getAllDangKy() {
    QList<dang_ky_xet_tuyen_ptr> list;
    QSqlError err = qx::dao::fetch_all_with_all_relation(list);
    if (err.isValid()) return std::nullopt;
    return list;
}

inline bool deleteDangKyByIds(long &id_thi_sinh, long &id_ma_nganh) {
    dang_ky_xet_tuyen_ptr temp;
    qx_query query(R"sql(
        DELETE FROM dang_ky_xet_tuyen
        WHERE id_thi_sinh = :id_thi_sinh
          AND id_ma_nganh = :id_ma_nganh
    )sql");

    query.bind(":id_thi_sinh", QVariant::fromValue(id_thi_sinh));
    query.bind(":id_ma_nganh", QVariant::fromValue(id_ma_nganh));

    QSqlError err = qx::dao::execute_query(query, temp);
    if (err.isValid())
        return false;
    else
        return true;
}

#endif // DANG_KY_XET_TUYEN_DAO_H
