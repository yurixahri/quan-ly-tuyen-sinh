#ifndef MONHOC_PAGE_H
#define MONHOC_PAGE_H

#include <QTableWidget>
#include <QLabel>
#include "db/monhoc_dao.h"

void fillMonHocTable(QTableWidget *table, QLabel *monhoc_size){
    auto list = getAllMonHoc();
    if (!list){
        qDebug() << "Error";
        return;
    }

    table->clearContents();
    table->setRowCount(0);
    //table->setColumnCount(2);
    //table->setHorizontalHeaderLabels({"ID môn học", "Tên môn học"});
    // uint32_t stt = 1;

    for (auto &item : *list){
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(item->id_monhoc)));
        table->setItem(row, 1, new QTableWidgetItem(item->ten_monhoc));
        qDebug() << item->id_monhoc << item->ten_monhoc;
        // ++stt;
    }
    monhoc_size->setText(QString::number(list->size()));
}

#endif // MONHOC_PAGE_H
