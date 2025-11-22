#ifndef NHOM_NGANH_PAGE_H
#define NHOM_NGANH_PAGE_H

#include <QTableWidget>
#include <QLabel>
#include "db/nhom_nganh_dao.h"

void fillNhomNganhTable(QTableWidget *table, QLabel *size){
    auto list = getAllNhomNganh();
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
        table->setItem(row, 0, new QTableWidgetItem(QString::number(item->id_nhom_nganh)));
        table->setItem(row, 1, new QTableWidgetItem(item->ten));
        // ++stt;
    }
    size->setText(QString::number(list->size()));
}

#endif // NHOM_NGANH_PAGE_H
