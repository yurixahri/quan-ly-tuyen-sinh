#ifndef UUTIEN_DAO_H
#define UUTIEN_DAO_H

#include "db/models/uutien.h"
#include "excel/read_excel.h"

inline bool addUuTien(long &id_thi_sinh, long &id_dtut, long &id_kvut){
    uutien_ptr adding;
    adding.reset(new uutien());
    adding->thi_sinh = std::make_shared<thi_sinh>(id_thi_sinh);
    adding->dtut = std::make_shared<ma_dtut>(id_dtut);
    adding->kvut = std::make_shared<ma_kvut>(id_kvut);

    QSqlError err = qx::dao::insert(adding);
    if (err.isValid())
        return false;
    else
        return true;
}

inline bool changeUuTien(uutien_ptr &item, long &id_thi_sinh, long &id_dtut, long &id_kvut){
    item->thi_sinh = std::make_shared<thi_sinh>(id_thi_sinh);
    item->dtut = std::make_shared<ma_dtut>(id_dtut);
    item->kvut = std::make_shared<ma_kvut>(id_kvut);

    QSqlError err = qx::dao::update(item);
    if (err.isValid())
        return false;
    else
        return true;
}

inline std::optional<QList<uutien_ptr>> getAllUuTien(){
    QList<uutien_ptr> list;
    qx::QxSession session;
    session += qx::dao::fetch_all_with_relation("*->*", list, session.database());

    if (!session.isValid()) {
        return std::nullopt;
    } else {
        return list;
    }
}

inline std::optional<uutien_ptr> getUuTienById(long &id){
    uutien_ptr item = std::make_shared<uutien>(id);
    qx::QxSession session;
    session += qx::dao::fetch_by_id_with_relation("*->*", item);

    if (!session.isValid()) {
        return std::nullopt;
    } else {
        return item;
    }
}

inline std::optional<QList<uutien_ptr>> getUuTienByThiSinhId(long &id_thi_sinh){
    QList<uutien_ptr> list;
    qx_query query;
    query.where("dt_kv_uutien.id_thi_sinh").isEqualTo(QVariant::fromValue(id_thi_sinh));
    QSqlError err = qx::dao::fetch_by_query_with_all_relation(query, list);

    if (err.isValid()) {
        return std::nullopt;
    } else {
        return list;
    }
}

inline bool deleteUuTienById(long &id){
    uutien_ptr item;
    item.reset(new uutien(id));
    QSqlError err = qx::dao::delete_by_id(item);
    if (err.isValid())
        return false;
    else
        return true;
}

inline bool deleteUuTienByThiSinhId(long &id_thi_sinh){
    auto list_opt = getUuTienByThiSinhId(id_thi_sinh);
    if (!list_opt) return false;
    auto list = list_opt.value();
    for (auto &item : list){
        QSqlError err = qx::dao::delete_by_id(item);
        if (err.isValid()) return false;
    }
    return true;
}

inline bool exportUuTienToExcel(QString &path){
    auto list_opt = getAllUuTien();
    if (!list_opt) return false;
    auto list = *list_opt;

    QXlsx::Document xlsx;
    // Title
    int row = 1;
    xlsx.write(row, 1, "DANH SÁCH ƯU TIÊN CỦA THÍ SINH");
    xlsx.mergeCells("A1:J1");
    // Header
    ++row;
    xlsx.write(row, 1, "STT");
    xlsx.write(row, 2, "Số báo danh");
    xlsx.write(row, 3, "Họ tên");
    xlsx.write(row, 4, "CMND/CCCD");
    xlsx.write(row, 5, "Ngày sinh");
    xlsx.write(row, 6, "Giới tính");
    xlsx.write(row, 7, "Đối tượng ưu tiên");
    xlsx.write(row, 8, "Điểm đtưt");
    xlsx.write(row, 9, "Khu vực ưu tiên");
    xlsx.write(row, 10, "Điểm kvưt");

    for (auto &item : list){
        ++row;

        xlsx.write(row, 1, row-2);
        xlsx.write(row, 2, item->thi_sinh->sbd);
        xlsx.write(row, 3, item->thi_sinh->ho_ten);
        xlsx.write(row, 4, item->thi_sinh->cccd);
        xlsx.write(row, 5, item->thi_sinh->ngay_sinh.toString("dd/MM/yyyy"));
        xlsx.write(row, 6, item->thi_sinh->gioi_tinh);
        xlsx.write(row, 7, item->dtut ? item->dtut->ma : "");
        xlsx.write(row, 8, item->dtut ? item->dtut->diem : NULL);
        xlsx.write(row, 9, item->kvut ? item->kvut->ma : "");
        xlsx.write(row, 10, item->kvut ? item->kvut->diem : NULL);
    }

    return xlsx.saveAs(path);
}
#endif // UUTIEN_DAO_H
