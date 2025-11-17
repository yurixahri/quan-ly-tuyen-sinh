#ifndef MONHOC_PAGE_H
#define MONHOC_PAGE_H

#include <QTableWidget>
#include "db/monhoc_dao.h"

void fillMonHocTable(QTableWidget *table){
    auto list = getAllMonHoc();
    if (!list){
        qDebug() << "Error";
        return;
    }

    table->clear();
    table->setRowCount(list->size() - 1);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"ID", "Mã môn học", "Tên môn học"});

    uint32_t stt = 1;

    for (auto &item : *list){
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(stt)));
        table->setItem(row, 1, new QTableWidgetItem(item->ma_monhoc));
        table->setItem(row, 2, new QTableWidgetItem(item->ten_monhoc));
    }
}

#endif // MONHOC_PAGE_H
