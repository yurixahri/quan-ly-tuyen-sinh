#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include "pages/monhoc_page.h"
#include "ui/add_mon_hoc_dialog.h"
#include "ui/change_mon_hoc_dialog.h"
#include "ui/custom_message_box.h"

#include "pages/tohop_page.h"
#include "ui/tohop/add_tohop_dialog.h"

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
    ui->stackedWidget->setCurrentIndex(4);
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
    ui->stackedWidget->setCurrentIndex(3);
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
    custom_message_box confirm("", "Bạn có chắc muốn xóa môn này?", custom_message_box::Question, true);
    if (confirm.exec() == QDialog::Accepted){
        if (!deleteToHopById(id)){
            custom_message_box("", "Xóa không thành công", custom_message_box::Error);
        }else{
            custom_message_box("", "Xóa thành công", custom_message_box::Information);
        }
        fillMonHocTable(ui->mon_hoc_table, ui->monhoc_size);
    }
}





