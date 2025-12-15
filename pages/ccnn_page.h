#ifndef CCNN_PAGE_H
#define CCNN_PAGE_H

#include <QTableWidget>
#include <QLabel>
#include "db/ma_chungchinn_dao.h"

void fillMaChungchinnTable(QTableWidget *table, QLabel *size){
    auto list = getAllMaChungchinn();
    if (!list){
        qDebug() << "Error fetching ma_chungchinn";
        return;
    }

    table->clearContents();
    table->setRowCount(0);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"ID", "Mã", "Tên"});

    for (auto &item : *list){
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(item->id)));
        table->setItem(row, 1, new QTableWidgetItem(item->ma));
        table->setItem(row, 2, new QTableWidgetItem(item->ten));
    }

    table->setColumnHidden(0, true);
    size->setText(QString::number(list->size()));
}

#endif // CCNN_PAGE_H
