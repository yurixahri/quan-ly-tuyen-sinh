#ifndef THI_SINH_PAGE_H
#define THI_SINH_PAGE_H

#include <QTableWidget>
#include <QLabel>
#include "db/thi_sinh_dao.h"

void fillThiSinhTable(QTableWidget *table, QLabel *size){
    auto list = getAllThiSinh();
    if (!list){
        qDebug() << "Error";
        return;
    }
    table->clearContents();
    table->setRowCount(0);
    table->setColumnCount(8);
    table->setHorizontalHeaderLabels({"ID", "CCCD", "Họ tên", "Ngày sinh", "Giới tính", "Email", "SDT", "Mã định danh"});
    // uint32_t stt = 1;

    for (auto &item : *list){
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(item->id)));
        table->setItem(row, 1, new QTableWidgetItem(item->cccd));
        table->setItem(row, 2, new QTableWidgetItem(item->ho_ten));
        table->setItem(row, 3, new QTableWidgetItem(item->ngay_sinh.toString() ));
        table->setItem(row, 4, new QTableWidgetItem(item->gioi_tinh));
        table->setItem(row, 5, new QTableWidgetItem(item->email));
        table->setItem(row, 6, new QTableWidgetItem(item->sdt));
        table->setItem(row, 7, new QTableWidgetItem(item->ma_dinh_danh));
        // ++stt;
    }

    table->setColumnHidden(0, true);
    size->setText(QString::number(list->size()));
}

#endif // THI_SINH_PAGE_H
