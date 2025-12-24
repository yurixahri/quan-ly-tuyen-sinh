#ifndef MA_NGANH_PAGE_H
#define MA_NGANH_PAGE_H

#include <QTableWidget>
#include <QLabel>
#include "db/ma_nganh_dao.h"

void fillMaNganhTable(QTableWidget *table, QLabel *size){
    auto list = getAllMaNganh();
    if (!list){
        qDebug() << "Error";
        return;
    }
    table->clearContents();
    table->setRowCount(0);
    table->setColumnCount(7);
    table->setHorizontalHeaderLabels({"ID", "Mã ngành", "Tên ngành", "Nhóm ngành", "Tổ hợp", "Chỉ tiêu", "Ghi chú"});
    // uint32_t stt = 1;
    for (auto &item : *list){
        QString list_tohop;
        QString list_ptxt;
        for (auto &tohop : item->list_tohop)
            list_tohop += tohop->tohop->ma_tohop + ", ";

        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem( QString::number(item->id) ));
        table->setItem(row, 1, new QTableWidgetItem(item->nganh->ma_nganh));
        table->setItem(row, 2, new QTableWidgetItem(item->nganh->ten_nganh));
        table->setItem(row, 3, new QTableWidgetItem(item->nganh->nhom_nganh->ten));
        table->setItem(row, 4, new QTableWidgetItem(list_tohop));
        table->setItem(row, 5, new QTableWidgetItem(QString::number(item->chi_tieu)));
        table->setItem(row, 6, new QTableWidgetItem(item->ghi_chu));
        // ++stt;
    }

    table->setColumnHidden(0, true);
    size->setText(QString::number(list->size()));
}

#endif // MA_NGANH_PAGE_H
