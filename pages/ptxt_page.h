#ifndef PTXT_PAGE_H
#define PTXT_PAGE_H

#include <QTableWidget>
#include <QLabel>
#include "db/ptxt_dao.h"

void fillPtxtTable(QTableWidget *table, QLabel *size){
    auto list = getAllPtxt();
    if (!list){
        qDebug() << "Error";
        return;
    }
    table->clearContents();
    table->setRowCount(0);
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({"ID", "Mã", "Tên", "Thang điểm", "Mô tả"});
    // uint32_t stt = 1;

    for (auto &item : *list){
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(item->id)));
        table->setItem(row, 1, new QTableWidgetItem(item->ma));
        table->setItem(row, 2, new QTableWidgetItem(item->ten));
        table->setItem(row, 3, new QTableWidgetItem(QString::number(item->thang_diem)));
        table->setItem(row, 4, new QTableWidgetItem(item->mo_ta));
        // ++stt;
    }

    table->setColumnHidden(0, true);
    size->setText(QString::number(list->size()));
}

#endif // PTXT_PAGE_H
