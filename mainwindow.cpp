#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include <QFileDialog>
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

#include "pages/ptxt_page.h"
#include "ui/ptxt/ptxt_dialog.h"

#include "pages/thi_sinh_page.h"
#include "ui/thi_sinh/thi_sinh_dialog.h"
#include "ui/thi_sinh/thi_sinh_detail.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
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

void MainWindow::on_delete_all_monhoc_clicked(){
    custom_message_box confirm("", "Bạn có chắc muốn xóa tất cả môn học?", custom_message_box::Question, true);
    if (confirm.exec() == QDialog::Accepted){
        if (!deleteAllMonHoc()){
            custom_message_box("", "Xóa không thành công", custom_message_box::Error).exec();
        }else{
            custom_message_box("", "Xóa thành công", custom_message_box::Information).exec();
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

void MainWindow::on_delete_all_tohop_clicked(){
    custom_message_box confirm("", "Bạn có chắc muốn xóa tất cả tổ hợp?", custom_message_box::Question, true);
    if (confirm.exec() == QDialog::Accepted){
        if (!deleteAllToHop()){
            custom_message_box("", "Xóa không thành công", custom_message_box::Error).exec();
        }else{
            custom_message_box("", "Xóa thành công", custom_message_box::Information).exec();
        }
        fillToHopTable(ui->tohop_mon_table, ui->tohop_size);
    }
}

void MainWindow::on_import_tohop_clicked(){
    QString path = QFileDialog::getOpenFileName(this, "Chọn file", "./", "Excel (*.xlsx)");
    if (!path.isEmpty()){
        importTohop(path);
    }
    fillToHopTable(ui->tohop_mon_table, ui->tohop_size);
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

void MainWindow::on_ma_nganh_import_excel_clicked(){
    QString path = QFileDialog::getOpenFileName(this, "Chọn file", "./", "Excel (*.xlsx)");
    if (!path.isEmpty()){
        importMaNganh(path);
    }
    fillMaNganhTable(ui->ma_nganh_table, ui->ma_nganh_size);
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

void MainWindow::on_delete_all_ma_nganh_clicked(){
    custom_message_box confirm("", "Bạn có chắc muốn xóa tất cả mã ngành?", custom_message_box::Question, true);
    if (confirm.exec() == QDialog::Accepted){
        if (!deleteAllMaNganh()){
            custom_message_box("", "Xóa không thành công", custom_message_box::Error).exec();
        }else{
            custom_message_box("", "Xóa thành công", custom_message_box::Information).exec();
        }
        fillMaNganhTable(ui->ma_nganh_table, ui->ma_nganh_size);
    }
}

/* ptxt */

void MainWindow::on_ptxt_button_clicked(){
    ui->stackedWidget->setCurrentIndex(6);
    fillPtxtTable(ui->ptxt_table, ui->ptxt_size);
}


void MainWindow::on_add_ptxt_button_clicked(){
    ptxt_dialog dlg(ptxt_dialog::ADD, this);

    if (dlg.exec() == QDialog::Accepted){
        fillPtxtTable(ui->ptxt_table, ui->ptxt_size);
    }
}

void MainWindow::on_import_ptxt_clicked(){
    QString path = QFileDialog::getOpenFileName(this, "Chọn file", "./", "Excel (*.xlsx)");
    if (!path.isEmpty()){
        importPtxt(path);
    }
    fillPtxtTable(ui->ptxt_table, ui->ptxt_size);
}

void MainWindow::on_ptxt_table_customContextMenuRequested(const QPoint &pos){
    QTableWidgetItem* item = ui->ptxt_table->itemAt(pos);

    if (item){
        QMenu contextMenu(tr(""), this);
        QAction* del = new QAction("Xóa", this);
        QAction* change = new QAction("Thay đổi", this);
        contextMenu.addAction(del);
        contextMenu.addAction(change);

        connect(change, &QAction::triggered, this, [=](){
            updatePtxt(ui->ptxt_table->item(item->row(), 0)->text().toLong());
        });

        connect(del, &QAction::triggered, this, [=](){
            deletePtxt(ui->ptxt_table->item(item->row(), 0)->text().toLong());
        });
        contextMenu.exec(ui->ptxt_table->viewport()->mapToGlobal(pos));
        // qDebug() << item->;
    }
}

void MainWindow::updatePtxt(long id){
    auto item = getPtxtById(id);
    if (item){
        ptxt_dialog dlg(ptxt_dialog::CHANGE, this);
        dlg.setEditItem(*item);

        if (dlg.exec() == QDialog::Accepted){
            fillPtxtTable(ui->ptxt_table, ui->ptxt_size);
        }
    }
}

void MainWindow::deletePtxt(long id){
    custom_message_box confirm("", "Bạn có chắc muốn xóa phương thức xét tuyển này?", custom_message_box::Question, true);
    if (confirm.exec() == QDialog::Accepted){
        if (!deletePtxtById(id)){
            custom_message_box("", "Xóa không thành công", custom_message_box::Error).exec();
        }else{
            custom_message_box("", "Xóa thành công", custom_message_box::Information).exec();
        }
        fillPtxtTable(ui->ptxt_table, ui->ptxt_size);
    }
}

// thi sinh

void MainWindow::on_thi_sinh_button_clicked(){
    ui->stackedWidget->setCurrentIndex(7);
    fillThiSinhTable(ui->thi_sinh_table, ui->thi_sinh_size);
}

void MainWindow::on_add_thi_sinh_button_clicked(){
    thi_sinh_dialog dlg(thi_sinh_dialog::ADD, this);

    if (dlg.exec() == QDialog::Accepted){
        fillThiSinhTable(ui->thi_sinh_table, ui->thi_sinh_size);
    }
}

void MainWindow::on_thi_sinh_table_customContextMenuRequested(const QPoint &pos){
    QTableWidgetItem* item = ui->thi_sinh_table->itemAt(pos);

    if (item){
        QMenu contextMenu(tr("Context Menu"), this);
        QAction* del = new QAction("Xóa", this);
        QAction* change = new QAction("Thay đổi", this);
        QAction* detail = new QAction("Chi tiết", this);
        contextMenu.addAction(change);
        contextMenu.addAction(detail);
        contextMenu.addAction(del);

        connect(change, &QAction::triggered, this, [=](){
            updateThiSinh(ui->thi_sinh_table->item(item->row(), 0)->text().toLong());
        });

        connect(del, &QAction::triggered, this, [=](){
            deleteThiSinh(ui->thi_sinh_table->item(item->row(), 0)->text().toLong());
        });

        connect(detail, &QAction::triggered, this, [=](){
            thiSinhDetail(ui->thi_sinh_table->item(item->row(), 0)->text().toLong());
        });
        contextMenu.exec(ui->thi_sinh_table->viewport()->mapToGlobal(pos));
    }
}

void MainWindow::updateThiSinh(long id){
    auto thiSinh = getThiSinhById(id);
    if (thiSinh){
        thi_sinh_dialog dlg(thi_sinh_dialog::CHANGE, this);
        dlg.setEditItem(*thiSinh);

        if (dlg.exec() == QDialog::Accepted){
            fillThiSinhTable(ui->thi_sinh_table, ui->thi_sinh_size);
        }
    }
}

void MainWindow::deleteThiSinh(long id){
    custom_message_box confirm("", "Bạn có chắc muốn xóa thí sinh này?", custom_message_box::Question, true);
    if (confirm.exec() == QDialog::Accepted){
        if (!deleteThiSinhById(id)){
            custom_message_box("", "Xóa không thành công", custom_message_box::Error).exec();
        }else{
            custom_message_box("", "Xóa thành công", custom_message_box::Information).exec();
        }
        fillThiSinhTable(ui->thi_sinh_table, ui->thi_sinh_size);
    }
}

void MainWindow::thiSinhDetail(long id){
    auto item = getThiSinhById(id);
    if (item){
        thi_sinh_detail dlg(this);
        dlg.setThiSinh(*item);
        dlg.exec();
    }
}

void MainWindow::on_import_sat_button_clicked(){
    QString path = QFileDialog::getOpenFileName(this, "Chọn file", "./", "Excel (*.xlsx)");
    if (!path.isEmpty()){
        importDiemSat(path);
    }
    fillThiSinhTable(ui->thi_sinh_table, ui->thi_sinh_size);
}

void MainWindow::on_import_ccnn_button_clicked(){
    QString path = QFileDialog::getOpenFileName(this, "Chọn file", "./", "Excel (*.xlsx)");
    if (!path.isEmpty()){
        importCCNN(path);
    }
    fillThiSinhTable(ui->thi_sinh_table, ui->thi_sinh_size);
}

void MainWindow::on_import_hocba_button_clicked(){
    QString path = QFileDialog::getOpenFileName(this, "Chọn file", "./", "Excel (*.xlsx)");
    if (!path.isEmpty()){
        importHocBa(path);
    }
    fillThiSinhTable(ui->thi_sinh_table, ui->thi_sinh_size);
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}

void MainWindow::on_close_clicked(){
    QCoreApplication::quit();
}






