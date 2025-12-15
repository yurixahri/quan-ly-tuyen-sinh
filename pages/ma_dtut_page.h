#ifndef MA_DTUT_PAGE_H
#define MA_DTUT_PAGE_H

#include <QTableWidget>
#include <QLabel>
#include "db/ma_dtut_dao.h"

void fillMaDtutTable(QTableWidget *table, QLabel *size){
    auto list = getAllMaDtut();
    if (!list){
        qDebug() << "Error fetching ma_dtut";
        return;
    }

    table->clearContents();
    table->setRowCount(0);
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"ID", "Mã", "Tên", "Điểm"});

    for (auto &item : *list){
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(item->id)));
        table->setItem(row, 1, new QTableWidgetItem(item->ma));
        table->setItem(row, 2, new QTableWidgetItem(item->ten));
        table->setItem(row, 3, new QTableWidgetItem(QString::number(item->diem)));
    }

    table->setColumnHidden(0, true);
    size->setText(QString::number(list->size()));
}

#endif // MA_DTUT_PAGE_H
