#ifndef MA_THANHTICH_PAGE_H
#define MA_THANHTICH_PAGE_H

#include <QTableWidget>
#include <QLabel>
#include "db/ma_thanhtich_dao.h"

void fillMaThanhTichTable(QTableWidget *table, QLabel *size){
    auto list = getAllMaThanhTich();
    if (!list){
        qDebug() << "Error fetching ma_thanhtich";
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

#endif // MA_THANHTICH_PAGE_H
