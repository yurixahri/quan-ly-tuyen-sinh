#ifndef TOHOP_PAGE_H
#define TOHOP_PAGE_H

#include <QTableWidget>
#include <QLabel>
#include "db/tohop_dao.h"
#include "db/monhoc_dao.h"

void fillToHopTable(QTableWidget *table, QLabel *size){
    auto list = getAllToHop();
    if (!list){
        qDebug() << "Error";
        return;
    }

    table->clearContents();
    table->setRowCount(0);
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({"ID", "Mã tổ hợp", "Môn học"});
    // uint32_t stt = 1;

    for (auto &item : *list){
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(item->id_tohop)));
        table->setItem(row, 1, new QTableWidgetItem(item->ma_tohop));
        table->setItem(row, 2, new QTableWidgetItem(item->mon_1->ten_monhoc+", "+item->mon_2->ten_monhoc+", "+item->mon_3->ten_monhoc));
        // ++stt;
    }

    table->setColumnHidden(0, true);
    size->setText(QString::number(list->size()));
}

#endif // TOHOP_PAGE_H
