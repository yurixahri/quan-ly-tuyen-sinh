#ifndef TOHOP_DAO_H
#define TOHOP_DAO_H

#include <QApplication>

#include "db/models/to_hop_mon.h"
#include "excel/read_excel.h"
#include "utils/string.h"
#include "db/monhoc_dao.h"
#include "ui/custom_message_box.h"
#include "ui/components/progressbar.h"

inline bool addToHop(QString &ma_tohop, long &id_mon_1, long &id_mon_2, long &id_mon_3){
    tohop_mon_ptr tohop_adding;
    tohop_adding.reset(new tohop_mon());
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
    tohop_mon_ptr item = std::make_shared<tohop_mon>(id);
    QSqlError err = qx::dao::fetch_by_id(item);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return std::nullopt;
    } else {
        return item;
    }
}

inline std::optional<tohop_mon_ptr> getToHopByName(QString &name){
    QList<tohop_mon_ptr> list;
    qx_query query;
    query.where("ma_tohop").isEqualTo(QVariant::fromValue(name));
    QSqlError err = qx::dao::fetch_by_query(query, list);

    if (err.isValid()) {
        qDebug() << "Fetch error:" << err.text();
        return std::nullopt;
    } else {
        if (list.isEmpty()) return std::nullopt;
        return list.first();
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

inline bool deleteAllToHop(){
    qx::QxSession session;
    session += qx::dao::delete_all<tohop_mon>(session.database());

    if (!session.isValid()) {
        return false;
    } else {
        return true;
    }
}

inline void importTohop(QString &path){
    qx::QxSession session;
    int index = 3;
    auto rows = readExcel(path);
    qDebug() << rows;
    if (rows->first().length() != 2){
        custom_message_box("", "Format excel không hợp lệ", custom_message_box::Error).exec();
        return;
    }else{
        progressBar progress_bar;
        progress_bar.setInitValue(rows->length());
        progress_bar.show();
        for (auto &row : *rows){
            auto monhoc_list = row[1].split(",");
            for (auto &monhoc : monhoc_list){
                trimLeadingAndTrailing(monhoc);
                upperCaseFirstLetter(monhoc);
            }
            if (monhoc_list.length() != 3){
                session.rollback();
                custom_message_box("", "Số lượng môn học phải bằng 3 cho 1 tổ hợp. Lỗi ở hàng "+QString::number(index)+" trong file excel", custom_message_box::Error).exec();
                return;
            }

            if (monhoc_list[0] == monhoc_list[1] || monhoc_list[0] == monhoc_list[2] || monhoc_list[1] == monhoc_list[2]){
                //session.rollback();
                custom_message_box("", "Có môn học bị trùng. Lỗi ở hàng "+QString::number(index)+" trong file excel", custom_message_box::Error).exec();
                                   return;
            }

            tohop_mon_ptr tohop_adding;
            tohop_adding.reset(new tohop_mon());
            trimLeadingAndTrailing(row[0]);
            tohop_adding->ma_tohop = row[0];
            while (true){
                if ( (tohop_adding->mon_1 = *getMonHocByName(monhoc_list[0])) ){
                    break;
                }else{
                    addMonHoc(monhoc_list[0]);
                }
            }
            while (true){
                if ( (tohop_adding->mon_2 = *getMonHocByName(monhoc_list[1])) ){
                    break;
                }else{
                    addMonHoc(monhoc_list[1]);
                }
            }
            while (true){
                if ( (tohop_adding->mon_3 = *getMonHocByName(monhoc_list[2])) ){
                    break;
                }else{
                    addMonHoc(monhoc_list[2]);
                }
            }

            QSqlError err = qx::dao::save(tohop_adding);
            if (err.isValid()){
                // custom_message_box("", "Có lỗi xảy ra khi thêm tổ hợp. Lỗi ở hàng "+QString::number(index)+" trong file excel", custom_message_box::Error).exec();
                //                    return;
                // break;
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

#endif // TOHOP_DAO_H
