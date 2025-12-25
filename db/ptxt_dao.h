#ifndef PTXT_DAO_H
#define PTXT_DAO_H

#include <QApplication>

#include "db/models/ptxt.h"
#include "utils/string.h"
#include "excel/read_excel.h"
#include "ui/custom_message_box.h"
#include "ui/components/progressbar.h"

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

inline std::optional<ptxt_ptr> getPtxtByName(QString &name){
    QList<ptxt_ptr> list;
    qx_query query;
    query.where("ma_xettuyen").isEqualTo(QVariant::fromValue(name));
    QSqlError err = qx::dao::fetch_by_query(query, list);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return std::nullopt;
    } else {
        if (list.isEmpty()) return std::nullopt;
        return list.first();
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

inline void importPtxt(QString &path){
    qx::QxSession session;
    int index = 3;
    auto rows = readExcel(path);
    qDebug() << rows;
    if (rows->first().length() != 3){
        custom_message_box("", "Format excel không hợp lệ", custom_message_box::Error).exec();
        return;
    }else{
        progressBar progress_bar;
        progress_bar.setInitValue(rows->length());
        progress_bar.show();
        for (auto &row : *rows){
            ptxt_ptr adding;
            adding.reset(new ptxt());
            trimLeadingAndTrailing(row[0]);
            trimLeadingAndTrailing(row[1]);
            trimLeadingAndTrailing(row[2]);
            adding->ma = row[0];
            adding->ten = row[1];
            adding->thang_diem = row[2].toFloat();

            QSqlError err = qx::dao::save(adding);
            if (err.isValid()){
                // progress_bar.close();
                // session.rollback();
                // custom_message_box("", "Có lỗi xảy ra khi thêm phương thức xét tuyển. Lỗi ở hàng "+QString::number(index)+" trong file excel", custom_message_box::Error).exec();
                // return;
            }
            if (progress_bar.is_closed){
                session.rollback();
                return;
            }
            ++index;
            progress_bar.setCurrentValue(index-3);
            QApplication::processEvents();
        }
    }
}

inline bool exportPtxtToExcel(QString &path){
    auto list_opt = getAllPtxt();
    if (!list_opt) return false;
    auto list = *list_opt;

    QXlsx::Document xlsx;
    // Title
    int row = 1;
    xlsx.write(row, 1, "BẢNG PHƯƠNG THỨC XÉT TUYỂN");
    xlsx.mergeCells("A1:D1");
    // Header
    ++row;
    xlsx.write(row, 1, "STT");
    xlsx.write(row, 2, "Mã PTXT");
    xlsx.write(row, 3, "Tên PTXT");
    xlsx.write(row, 4, "Thang điểm");

    for (auto &item : list){
        ++row;
        QString ma= !item->ma.isEmpty() ? item->ma : "";
        QString ten= !item->ten.isEmpty() ? item->ten : "";

        xlsx.write(row, 1, row-2);
        xlsx.write(row, 2, ma);
        xlsx.write(row, 3, ten);
        xlsx.write(row, 4, item->thang_diem);
    }

    return xlsx.saveAs(path);
}

#endif // PTXT_DAO_H
