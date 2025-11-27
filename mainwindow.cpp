#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include "pages/monhoc_page.h"
#include "ui/add_mon_hoc_dialog.h"
#include "ui/change_mon_hoc_dialog.h"
#include "ui/custom_message_box.h"

#include "pages/tohop_page.h"
#include "ui/tohop/add_tohop_dialog.h"

#include "pages/nhom_nganh_page.h"
#include "ui/nhom_nganh/nhom_nganh_dialog.h"

#include "pages/nganh_page.h"
#include "ui/nganh/nganh_dialog.h"

#include "pages/ma_nganh_page.h"
#include "ui/ma_nganh/ma_nganh_dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}


// mon hoc page

void MainWindow::on_monhoc_button_clicked(){
    ui->stackedWidget->setCurrentIndex(5);
    fillMonHocTable(ui->mon_hoc_table, ui->monhoc_size);
    connect(ui->mon_hoc_table, &QTableWidget::customContextMenuRequested,
            this, &MainWindow::monHocTableContextMenu);
}


void MainWindow::on_add_monhoc_button_clicked(){
    add_mon_hoc_dialog dlg(this);

    if (dlg.exec() == QDialog::Accepted){
        fillMonHocTable(ui->mon_hoc_table, ui->monhoc_size);
    }
}

void MainWindow::monHocTableContextMenu(const QPoint& pos){
    QTableWidgetItem* item = ui->mon_hoc_table->itemAt(pos);

    if (item){
        QMenu contextMenu(tr("Context Menu"), this);
        QAction* del = new QAction("Xóa", this);
        QAction* change = new QAction("Thay đổi", this);
        contextMenu.addAction(del);
        contextMenu.addAction(change);

        connect(change, &QAction::triggered, this, [=](){
            updateMonHoc(ui->mon_hoc_table->item(item->row(), 0)->text().toLong());
        });

        connect(del, &QAction::triggered, this, [=](){
            deleteMonHoc(ui->mon_hoc_table->item(item->row(), 0)->text().toLong());
        });
        contextMenu.exec(ui->mon_hoc_table->viewport()->mapToGlobal(pos));
        // qDebug() << item->;
    }
}

void MainWindow::updateMonHoc(long id){
    auto mon_hoc = getMonHocById(id);
    if (mon_hoc){
        change_mon_hoc_dialog dlg(this);
        dlg.setMonHoc(*mon_hoc);

        if (dlg.exec() == QDialog::Accepted){
            fillMonHocTable(ui->mon_hoc_table, ui->monhoc_size);
        }
    }
}

void MainWindow::deleteMonHoc(long id){
    custom_message_box confirm("", "Bạn có chắc muốn xóa môn này?", custom_message_box::Question, true);
    if (confirm.exec() == QDialog::Accepted){
        if (!deleteMonHocById(id)){
            custom_message_box("", "Xóa không thành công", custom_message_box::Error);
        }else{
            custom_message_box("", "Xóa thành công", custom_message_box::Information);
        }
        fillMonHocTable(ui->mon_hoc_table, ui->monhoc_size);
    }
}


// to hop
void MainWindow::on_tohop_button_clicked(){
    ui->stackedWidget->setCurrentIndex(4);
    fillToHopTable(ui->tohop_mon_table, ui->tohop_size);
}


void MainWindow::on_add_tohop_button_clicked(){
    add_tohop_dialog dlg(add_tohop_dialog::ADD, this);
    if (dlg.exec() == QDialog::Accepted){
        fillToHopTable(ui->tohop_mon_table, ui->tohop_size);
    }
}

void MainWindow::on_tohop_mon_table_customContextMenuRequested(const QPoint &pos){
    QTableWidgetItem* item = ui->tohop_mon_table->itemAt(pos);

    if (item){
        QMenu contextMenu(tr(""), this);
        QAction* del = new QAction("Xóa", this);
        QAction* change = new QAction("Thay đổi", this);
        contextMenu.addAction(del);
        contextMenu.addAction(change);

        connect(change, &QAction::triggered, this, [=](){
            updateToHop(ui->tohop_mon_table->item(item->row(), 0)->text().toLong());
        });

        connect(del, &QAction::triggered, this, [=](){
            deleteToHop(ui->tohop_mon_table->item(item->row(), 0)->text().toLong());
        });
        contextMenu.exec(ui->tohop_mon_table->viewport()->mapToGlobal(pos));
        // qDebug() << item->;
    }
}

void MainWindow::updateToHop(long id){
    auto item = getToHopById(id);
    if (item){
        add_tohop_dialog dlg(add_tohop_dialog::CHANGE, this);
        dlg.setToHop(*item);

        if (dlg.exec() == QDialog::Accepted){
            fillToHopTable(ui->tohop_mon_table, ui->tohop_size);
        }
    }
}

void MainWindow::deleteToHop(long id){
    custom_message_box confirm("", "Bạn có chắc muốn xóa tổ hợp này?", custom_message_box::Question, true);
    if (confirm.exec() == QDialog::Accepted){
        if (!deleteToHopById(id)){
            custom_message_box("", "Xóa không thành công", custom_message_box::Error).exec();
        }else{
            custom_message_box("", "Xóa thành công", custom_message_box::Information).exec();
        }
        fillToHopTable(ui->tohop_mon_table, ui->tohop_size);
    }
}

/* nhom nganh */

void MainWindow::on_nhom_nganh_button_clicked(){
    ui->stackedWidget->setCurrentIndex(3);
    fillNhomNganhTable(ui->nhom_nganh_table, ui->nhom_nganh_size);
}

void MainWindow::on_add_nhom_nganh_button_clicked(){
    nhom_nganh_dialog dlg(nhom_nganh_dialog::ADD, this);

    if (dlg.exec() == QDialog::Accepted){
        fillNhomNganhTable(ui->nhom_nganh_table, ui->nhom_nganh_size);
    }
}

void MainWindow::on_nhom_nganh_table_customContextMenuRequested(const QPoint &pos){
    QTableWidgetItem* item = ui->nhom_nganh_table->itemAt(pos);

    if (item){
        QMenu contextMenu(tr(""), this);
        QAction* del = new QAction("Xóa", this);
        QAction* change = new QAction("Thay đổi", this);
        contextMenu.addAction(del);
        contextMenu.addAction(change);

        connect(change, &QAction::triggered, this, [=](){
            updateNhomNganh(ui->nhom_nganh_table->item(item->row(), 0)->text().toLong());
        });

        connect(del, &QAction::triggered, this, [=](){
            deleteNhomNganh(ui->nhom_nganh_table->item(item->row(), 0)->text().toLong());
        });
        contextMenu.exec(ui->nhom_nganh_table->viewport()->mapToGlobal(pos));
        // qDebug() << item->;
    }
}

void MainWindow::updateNhomNganh(long id){
    auto item = getNhomNganhById(id);
    if (item){
        nhom_nganh_dialog dlg(nhom_nganh_dialog::CHANGE, this);
        dlg.setEditItem(*item);

        if (dlg.exec() == QDialog::Accepted){
            fillNhomNganhTable(ui->nhom_nganh_table, ui->nhom_nganh_size);
        }
    }
}

void MainWindow::deleteNhomNganh(long id){
    custom_message_box confirm("", "Bạn có chắc muốn xóa nhóm ngành này?", custom_message_box::Question, true);
    if (confirm.exec() == QDialog::Accepted){
        if (!deleteNhomNganhById(id)){
            custom_message_box("", "Xóa không thành công", custom_message_box::Error).exec();
        }else{
            custom_message_box("", "Xóa thành công", custom_message_box::Information).exec();
        }
        fillNhomNganhTable(ui->nhom_nganh_table, ui->nhom_nganh_size);
    }
}

/* nganh */

void MainWindow::on_nganh_button_clicked(){
    ui->stackedWidget->setCurrentIndex(2);
    fillNganhTable(ui->nganh_table, ui->nganh_size);
}

void MainWindow::on_add_nganh_button_clicked(){
    nganh_dialog dlg(nganh_dialog::ADD, this);

    if (dlg.exec() == QDialog::Accepted){
        fillNganhTable(ui->nganh_table, ui->nganh_size);
    }
}

void MainWindow::on_nganh_table_customContextMenuRequested(const QPoint &pos){
    QTableWidgetItem* item = ui->nganh_table->itemAt(pos);

    if (item){
        QMenu contextMenu(tr(""), this);
        QAction* del = new QAction("Xóa", this);
        QAction* change = new QAction("Thay đổi", this);
        contextMenu.addAction(del);
        contextMenu.addAction(change);

        connect(change, &QAction::triggered, this, [=](){
            updateNganh(ui->nganh_table->item(item->row(), 0)->text().toLong());
        });

        connect(del, &QAction::triggered, this, [=](){
            deleteNganh(ui->nganh_table->item(item->row(), 0)->text().toLong());
        });
        contextMenu.exec(ui->nganh_table->viewport()->mapToGlobal(pos));
        // qDebug() << item->;
    }
}

void MainWindow::updateNganh(long id){
    auto item = getNganhById(id);
    if (item){
        nganh_dialog dlg(nganh_dialog::CHANGE, this);
        dlg.setEditItem(*item);

        if (dlg.exec() == QDialog::Accepted){
            fillNganhTable(ui->nganh_table, ui->nganh_size);
        }
    }
}

void MainWindow::deleteNganh(long id){
    custom_message_box confirm("", "Bạn có chắc muốn xóa ngành này?", custom_message_box::Question, true);
    if (confirm.exec() == QDialog::Accepted){
        if (!deleteNganhById(id)){
            custom_message_box("", "Xóa không thành công", custom_message_box::Error).exec();
        }else{
            custom_message_box("", "Xóa thành công", custom_message_box::Information).exec();
        }
        fillNganhTable(ui->nganh_table, ui->nganh_size);
    }
}

/* ma nganh */
void MainWindow::on_ma_nganh_button_clicked(){
    ui->stackedWidget->setCurrentIndex(1);
    fillMaNganhTable(ui->ma_nganh_table, ui->ma_nganh_size);
}

void MainWindow::on_add_ma_nganh_button_clicked(){
    ma_nganh_dialog dlg(ma_nganh_dialog::ADD, this);

    if (dlg.exec() == QDialog::Accepted){
        fillMaNganhTable(ui->ma_nganh_table, ui->ma_nganh_size);
    }
}

void MainWindow::on_ma_nganh_table_customContextMenuRequested(const QPoint &pos){
    QTableWidgetItem* item = ui->ma_nganh_table->itemAt(pos);

    if (item){
        QMenu contextMenu(tr(""), this);
        QAction* del = new QAction("Xóa", this);
        QAction* change = new QAction("Thay đổi", this);
        contextMenu.addAction(del);
        contextMenu.addAction(change);

        connect(change, &QAction::triggered, this, [=](){
            updateMaNganh(ui->ma_nganh_table->item(item->row(), 0)->text().toLong());
        });

        connect(del, &QAction::triggered, this, [=](){
            deleteMaNganh(ui->ma_nganh_table->item(item->row(), 0)->text().toLong());
        });
        contextMenu.exec(ui->ma_nganh_table->viewport()->mapToGlobal(pos));
        // qDebug() << item->;
    }
}

void MainWindow::updateMaNganh(long id){
    auto item = getMaNganhById(id);
    if (item){
        ma_nganh_dialog dlg(ma_nganh_dialog::CHANGE, this);
        dlg.setEditItem(*item);

        if (dlg.exec() == QDialog::Accepted){
            fillMaNganhTable(ui->ma_nganh_table, ui->ma_nganh_size);
        }
    }
}

void MainWindow::deleteMaNganh(long id){
    custom_message_box confirm("", "Bạn có chắc muốn xóa mã ngành này?", custom_message_box::Question, true);
    if (confirm.exec() == QDialog::Accepted){
        if (!deleteMaNganhById(id)){
            custom_message_box("", "Xóa không thành công", custom_message_box::Error).exec();
        }else{
            custom_message_box("", "Xóa thành công", custom_message_box::Information).exec();
        }
        fillMaNganhTable(ui->ma_nganh_table, ui->ma_nganh_size);
    }
}

