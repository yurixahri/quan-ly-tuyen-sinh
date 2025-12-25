#ifndef DANG_KY_XET_TUYEN_DAO_H
#define DANG_KY_XET_TUYEN_DAO_H

#include <QApplication>

#include "db/models/dang_ky_xet_tuyen.h"
#include "utils/string.h"
#include "excel/read_excel.h"
#include "ui/components/progressbar.h"
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
        WHERE id_thi_sinh = :id_thi_sinh
          AND id_ma_nganh = :id_ma_nganh
    )sql");

    query.bind(":diem_xt", diem);
    query.bind(":trang_thai", trang_thai.trimmed());
    if (id_ptxt > 0) query.bind(":id_ptxt", QVariant::fromValue(id_ptxt));
    else  query.bind(":id_ptxt", QVariant(QVariant::Int)); // NULL
    query.bind(":id_thi_sinh", QVariant::fromValue(item->id_thi_sinh));
    query.bind(":id_ma_nganh", QVariant::fromValue(item->ma_nganh->id));
    qDebug() << item->id_thi_sinh << item->ma_nganh->id;
    QSqlError err = qx::dao::execute_query(query, item);
    if (err.isValid())
        return false;
    else
        return true;
}

inline std::optional<dang_ky_xet_tuyen_ptr> getDangKyByIds(long &id_thi_sinh, long &id_ma_nganh) {
    dang_ky_xet_tuyen_ptr item(new dang_ky_xet_tuyen());
    qx_query query;
    query.where("dang_ky_xet_tuyen.id_thi_sinh").isEqualTo(QVariant::fromValue(id_thi_sinh))
        .and_("dang_ky_xet_tuyen.id_ma_nganh").isEqualTo(QVariant::fromValue(id_ma_nganh));

    QSqlError err = qx::dao::fetch_by_query_with_relation("*->*", query, item);
    if (err.isValid()) return std::nullopt;
    return item;
}

inline std::optional<QList<dang_ky_xet_tuyen_ptr>> getDangKyByThiSinhId(long &id_thi_sinh) {
    QList<dang_ky_xet_tuyen_ptr> list;
    qx_query query;
    query.where("dang_ky_xet_tuyen.id_thi_sinh").isEqualTo(QVariant::fromValue(id_thi_sinh))
        .orderAsc("thu_tu");
    QSqlError err = qx::dao::fetch_by_query_with_relation("*->*", query, list);
    if (err.isValid()) return std::nullopt;
    return list;
}


inline std::optional<QList<dang_ky_xet_tuyen_ptr>> getAllDangKy() {
    QList<dang_ky_xet_tuyen_ptr> list;
    qx_query query;
    query.orderAsc("dang_ky_xet_tuyen.id_thi_sinh", "thu_tu");
    // QStringList relations;
    // relations << "id_ma_nganh->*" << "id_ptxt";
    QSqlError err = qx::dao::fetch_by_query_with_relation("*->*", query, list);
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

inline bool exportDKXTToExcel(QString &path){
    auto list_opt = getAllDangKy();
    if (!list_opt) return false;
    auto list = *list_opt;

    QXlsx::Document xlsx;
    // Title
    int row = 1;
    xlsx.write(row, 1, "DANH SÁCH NGUYỆN VỌNG CỦA THÍ SINH");
    xlsx.mergeCells("A1:L1");
    // Header
    ++row;
    xlsx.write(row, 1, "STT");
    xlsx.write(row, 2, "CMND/CCCD");
    xlsx.write(row, 3, "Thứ tự nguyện vọng");
    xlsx.write(row, 4, "Mã xét tuyển");
    xlsx.write(row, 5, "Tên xét tuyển");
    xlsx.write(row, 6, "PTXT");

    long id = 0;
    int thu_tu = 1;
    progressBar progress_bar;
    progress_bar.setInitValue(list.length());
    progress_bar.show();
    for (auto &item : list){
        if (progress_bar.is_closed){
            return true;
        }

        thi_sinh_ptr ts = std::make_shared<thi_sinh>(item->id_thi_sinh);
        QSqlError err = qx::dao::fetch_by_id(ts);
        item->thi_sinh = ts;
        ++row;
        if (item->thi_sinh->id != id){
            id = item->thi_sinh->id;
            thu_tu = 1;
        }
        xlsx.write(row, 1, row-2);
        xlsx.write(row, 2, item->thi_sinh->cccd.isEmpty() ? "" : item->thi_sinh->cccd) ;
        xlsx.write(row, 3, thu_tu);
        xlsx.write(row, 4, item->ma_nganh ? item->ma_nganh->nganh->ma_nganh : "");
        xlsx.write(row, 5, item->ma_nganh ? item->ma_nganh->nganh->ten_nganh : "");
        qDebug() << item->thi_sinh->id;
        ++thu_tu;

        progress_bar.setCurrentValue(row-2);
        QApplication::processEvents();
    }
    progress_bar.close();

    return xlsx.saveAs(path);
}

#endif // DANG_KY_XET_TUYEN_DAO_H
