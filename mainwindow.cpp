#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include <QFileDialog>
#include <QDialog>
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

#include "db/ma_nganh_dao.h"

#include "pages/ptxt_page.h"
#include "ui/ptxt/ptxt_dialog.h"

// new management pages & dialogs
#include "pages/ccnn_page.h"
#include "ui/ccnn/ccnn_dialog.h"
#include "pages/ma_thanhtich_page.h"
#include "ui/doat_giai/doatgiai_dialog.h"
#include "pages/ma_dtut_page.h"
#include "ui/dtut/dtut_dialog.h"
#include "pages/ma_kvut_page.h"
#include "ui/dtut/kvut_dialog.h"

#include "pages/thi_sinh_page.h"
#include "ui/thi_sinh/thi_sinh_dialog.h"
#include "ui/thi_sinh/thi_sinh_detail.h"

#include "pages/trang_chu_page.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    // Initialize and show the home dashboard page by default
    ui->stackedWidget->setCurrentIndex(0);
    TrangChuDashboard *dashboard = new TrangChuDashboard(ui->home_page);
    QVBoxLayout *layout = new QVBoxLayout(ui->home_page);
    layout->addWidget(dashboard);
    layout->setContentsMargins(0, 0, 0, 0);
    ui->home_page->setLayout(layout);
    dashboard->loadDashboardData();

    // Example shortcut: open CCNN manager with Ctrl+M
    // QShortcut *openCcnn = new QShortcut(QKeySequence("Ctrl+M"), this);
    // connect(openCcnn, &QShortcut::activated, this, &MainWindow::on_manage_ccnn_clicked);
}

MainWindow::~MainWindow(){
    delete ui;
}

// Home Dashboard Page
void MainWindow::on_home_button_clicked(){
    ui->stackedWidget->setCurrentIndex(0);
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

void MainWindow::on_export_ma_nganh_button_clicked(){
    QString path = QFileDialog::getSaveFileName(this, "Lưu file", "./ma_nganh.xlsx", "Excel (*.xlsx)");
    if (path.isEmpty()) return;

    if (exportMaNganhToExcel(path)){
        custom_message_box("", "Xuất thành công", custom_message_box::Information).exec();
    } else {
        custom_message_box("", "Xuất thất bại", custom_message_box::Error).exec();
    }
}
// ---- Management pages follow existing UI pattern ----

void MainWindow::on_ccnn_button_clicked(){
    ui->stackedWidget->setCurrentIndex(8);
    fillMaChungchinnTable(ui->ccnn_table, ui->ccnn_size);
}

void MainWindow::on_add_ccnn_button_clicked(){
    ccnn_dialog dlg(ccnn_dialog::ADD, this);
    if (dlg.exec() == QDialog::Accepted){
        fillMaChungchinnTable(ui->ccnn_table, ui->ccnn_size);
    }
}

void MainWindow::on_ccnn_table_customContextMenuRequested(const QPoint &pos){
    QTableWidgetItem* item = ui->ccnn_table->itemAt(pos);

    if (item){
        QMenu contextMenu(tr(""), this);
        QAction* del = new QAction("Xóa", this);
        QAction* change = new QAction("Thay đổi", this);
        contextMenu.addAction(del);
        contextMenu.addAction(change);

        connect(change, &QAction::triggered, this, [=](){
            updateMaChungchinn(ui->ccnn_table->item(item->row(), 0)->text().toLong());
        });

        connect(del, &QAction::triggered, this, [=](){
            deleteMaChungchinn(ui->ccnn_table->item(item->row(), 0)->text().toLong());
        });
        contextMenu.exec(ui->ccnn_table->viewport()->mapToGlobal(pos));
    }
}

void MainWindow::updateMaChungchinn(long id){
    auto item = getMaChungchinnById(id);
    if (item){
        ccnn_dialog dlg(ccnn_dialog::CHANGE, this);
        dlg.setEditItem(*item);
        if (dlg.exec() == QDialog::Accepted){
            fillMaChungchinnTable(ui->ccnn_table, ui->ccnn_size);
        }
    }
}

void MainWindow::deleteMaChungchinn(long id){
    custom_message_box confirm("", "Bạn có chắc muốn xóa chứng chỉ này?", custom_message_box::Question, true);
    if (confirm.exec() == QDialog::Accepted){
        if (!deleteMaChungchinnById(id)){
            custom_message_box("", "Xóa không thành công", custom_message_box::Error).exec();
        }else{
            custom_message_box("", "Xóa thành công", custom_message_box::Information).exec();
        }
        fillMaChungchinnTable(ui->ccnn_table, ui->ccnn_size);
    }
}

// thanh tich

void MainWindow::on_thanh_tich_button_clicked(){
    ui->stackedWidget->setCurrentIndex(9);
    fillMaThanhTichTable(ui->thanh_tich_table, ui->thanh_tich_size);
}

void MainWindow::on_add_thanh_tich_button_clicked(){
    doatgiai_dialog dlg(doatgiai_dialog::ADD, this);
    if (dlg.exec() == QDialog::Accepted){
        fillMaThanhTichTable(ui->thanh_tich_table, ui->thanh_tich_size);
    }
}

void MainWindow::on_thanh_tich_table_customContextMenuRequested(const QPoint &pos){
    QTableWidgetItem* item = ui->thanh_tich_table->itemAt(pos);

    if (item){
        QMenu contextMenu(tr(""), this);
        QAction* del = new QAction("Xóa", this);
        QAction* change = new QAction("Thay đổi", this);
        contextMenu.addAction(del);
        contextMenu.addAction(change);

        connect(change, &QAction::triggered, this, [=](){
            updateMaThanhTich(ui->thanh_tich_table->item(item->row(), 0)->text().toLong());
        });

        connect(del, &QAction::triggered, this, [=](){
            deleteMaThanhTich(ui->thanh_tich_table->item(item->row(), 0)->text().toLong());
        });
        contextMenu.exec(ui->thanh_tich_table->viewport()->mapToGlobal(pos));
    }
}

void MainWindow::updateMaThanhTich(long id){
    auto item = getMaThanhTichById(id);
    if (item){
        doatgiai_dialog dlg(doatgiai_dialog::CHANGE, this);
        dlg.setEditItem(*item);
        if (dlg.exec() == QDialog::Accepted){
            fillMaThanhTichTable(ui->thanh_tich_table, ui->thanh_tich_size);
        }
    }
}

void MainWindow::deleteMaThanhTich(long id){
    custom_message_box confirm("", "Bạn có chắc muốn xóa thành tích này?", custom_message_box::Question, true);
    if (confirm.exec() == QDialog::Accepted){
        if (!deleteMaThanhTichById(id)){
            custom_message_box("", "Xóa không thành công", custom_message_box::Error).exec();
        }else{
            custom_message_box("", "Xóa thành công", custom_message_box::Information).exec();
        }
        fillMaThanhTichTable(ui->thanh_tich_table, ui->thanh_tich_size);
    }
}

// doi tuong uu tien

void MainWindow::on_dtut_button_clicked(){
    ui->stackedWidget->setCurrentIndex(10);
    fillMaDtutTable(ui->dtut_table, ui->dtut_size);
}

void MainWindow::on_add_dtut_button_clicked(){
    dtut_dialog dlg(dtut_dialog::ADD, this);
    if (dlg.exec() == QDialog::Accepted){
        fillMaDtutTable(ui->dtut_table, ui->dtut_size);
    }
}

void MainWindow::on_dtut_table_customContextMenuRequested(const QPoint &pos){
    QTableWidgetItem* item = ui->dtut_table->itemAt(pos);

    if (item){
        QMenu contextMenu(tr(""), this);
        QAction* del = new QAction("Xóa", this);
        QAction* change = new QAction("Thay đổi", this);
        contextMenu.addAction(del);
        contextMenu.addAction(change);

        connect(change, &QAction::triggered, this, [=](){
            updateMaDtut(ui->dtut_table->item(item->row(), 0)->text().toLong());
        });

        connect(del, &QAction::triggered, this, [=](){
            deleteMaDtut(ui->dtut_table->item(item->row(), 0)->text().toLong());
        });
        contextMenu.exec(ui->dtut_table->viewport()->mapToGlobal(pos));
    }
}

void MainWindow::updateMaDtut(long id){
    auto item = getMaDtutById(id);
    if (item){
        dtut_dialog dlg(dtut_dialog::CHANGE, this);
        dlg.setEditItem(*item);
        if (dlg.exec() == QDialog::Accepted){
            fillMaDtutTable(ui->dtut_table, ui->dtut_size);
        }
    }
}

void MainWindow::deleteMaDtut(long id){
    custom_message_box confirm("", "Bạn có chắc muốn xóa điểm ưu tiên này?", custom_message_box::Question, true);
    if (confirm.exec() == QDialog::Accepted){
        if (!deleteMaDtutById(id)){
            custom_message_box("", "Xóa không thành công", custom_message_box::Error).exec();
        }else{
            custom_message_box("", "Xóa thành công", custom_message_box::Information).exec();
        }
        fillMaDtutTable(ui->dtut_table, ui->dtut_size);
    }
}

void MainWindow::on_kvut_button_clicked(){
    ui->stackedWidget->setCurrentIndex(11);
    fillMaKvutTable(ui->kvut_table, ui->kvut_size);
}

void MainWindow::on_add_kvut_button_clicked(){
    kvut_dialog dlg(kvut_dialog::ADD, this);
    if (dlg.exec() == QDialog::Accepted){
        fillMaKvutTable(ui->kvut_table, ui->kvut_size);
    }
}

void MainWindow::on_kvut_table_customContextMenuRequested(const QPoint &pos){
    QTableWidgetItem* item = ui->kvut_table->itemAt(pos);

    if (item){
        QMenu contextMenu(tr(""), this);
        QAction* del = new QAction("Xóa", this);
        QAction* change = new QAction("Thay đổi", this);
        contextMenu.addAction(del);
        contextMenu.addAction(change);

        connect(change, &QAction::triggered, this, [=](){
            updateMaKvut(ui->kvut_table->item(item->row(), 0)->text().toLong());
        });

        connect(del, &QAction::triggered, this, [=](){
            deleteMaKvut(ui->kvut_table->item(item->row(), 0)->text().toLong());
        });
        contextMenu.exec(ui->kvut_table->viewport()->mapToGlobal(pos));
    }
}

void MainWindow::updateMaKvut(long id){
    auto item = getMaKvutById(id);
    if (item){
        kvut_dialog dlg(kvut_dialog::CHANGE, this);
        dlg.setEditItem(*item);
        if (dlg.exec() == QDialog::Accepted){
            fillMaKvutTable(ui->kvut_table, ui->kvut_size);
        }
    }
}

void MainWindow::deleteMaKvut(long id){
    custom_message_box confirm("", "Bạn có chắc muốn xóa khu vực ưu tiên này?", custom_message_box::Question, true);
    if (confirm.exec() == QDialog::Accepted){
        if (!deleteMaKvutById(id)){
            custom_message_box("", "Xóa không thành công", custom_message_box::Error).exec();
        }else{
            custom_message_box("", "Xóa thành công", custom_message_box::Information).exec();
        }
        fillMaKvutTable(ui->kvut_table, ui->kvut_size);
    }
}


// ma nganh

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
void MainWindow::resetMaxThiSinhPageCount(){
    auto max_page_count = getThiSinhPageCount();
    ui->thi_sinh_current_page->setMaximum(max_page_count);
    ui->thi_sinh_current_page->setMinimum(1);
    ui->thi_sinh_total_page->setText(QString::number(max_page_count));
}


void MainWindow::on_thi_sinh_tim_kiem_editingFinished(){
    search = ui->thi_sinh_tim_kiem->text();
    on_thi_sinh_button_clicked();
}

void MainWindow::on_thi_sinh_button_clicked(){
    ui->stackedWidget->setCurrentIndex(7);
    fillThiSinhTable(ui->thi_sinh_table, ui->thi_sinh_size);
    ui->thi_sinh_current_page->setValue(1);
    resetMaxThiSinhPageCount();
}

void MainWindow::on_thi_sinh_current_page_editingFinished(){
    resetMaxThiSinhPageCount();
    uint page = ui->thi_sinh_current_page->value();
    setThiSinhPage(page);
    fillThiSinhTable(ui->thi_sinh_table, ui->thi_sinh_size);
}

void MainWindow::on_thi_sinh_current_page_valueChanged(int arg1){
    uint page = ui->thi_sinh_current_page->value();
    setThiSinhPage(page);
    fillThiSinhTable(ui->thi_sinh_table, ui->thi_sinh_size);
}

void MainWindow::on_thi_sinh_previous_page_clicked(){
    resetMaxThiSinhPageCount();
    ui->thi_sinh_current_page->stepDown();
    uint page = ui->thi_sinh_current_page->value();
    setThiSinhPage(page);
    fillThiSinhTable(ui->thi_sinh_table, ui->thi_sinh_size);
}

void MainWindow::on_thi_sinh_next_page_clicked(){
    resetMaxThiSinhPageCount();
    ui->thi_sinh_current_page->stepUp();
    uint page = ui->thi_sinh_current_page->value();
    setThiSinhPage(page);
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

void MainWindow::on_import_doatgiai_button_clicked(){
    QString path = QFileDialog::getOpenFileName(this, "Chọn file", "./", "Excel (*.xlsx)");
    if (!path.isEmpty()){
        importDoatGiai(path);
    }
    fillThiSinhTable(ui->thi_sinh_table, ui->thi_sinh_size);
}

void MainWindow::on_import_uutien_button_clicked(){
    QString path = QFileDialog::getOpenFileName(this, "Chọn file", "./", "Excel (*.xlsx)");
    if (!path.isEmpty()){
        importUutien(path);
    }
    fillThiSinhTable(ui->thi_sinh_table, ui->thi_sinh_size);
}

void MainWindow::on_import_dkxt_button_clicked(){
    QString path = QFileDialog::getOpenFileName(this, "Chọn file", "./", "Excel (*.xlsx)");
    if (!path.isEmpty()){
        importNguyenVong(path);
    }
    fillThiSinhTable(ui->thi_sinh_table, ui->thi_sinh_size);
}

// mouse event
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

void MainWindow::on_pushButton_clicked(){
    if(!this->isMaximized())
        this->showMaximized();
    else
        this->showNormal();
}

// export


void MainWindow::on_xuat_du_lieu_button_clicked(){
    ui->stackedWidget->setCurrentIndex(12);
}

void MainWindow::on_export_ma_nganh_clicked(){
    QString file_name = QFileDialog::getSaveFileName(this,
                                                    tr("Lưu file"), QDir::homePath(),
                                                    tr("Excel (*.xlsx)"));
    if (!file_name.isEmpty()){
        if(!exportMaNganhToExcel(file_name)){
            custom_message_box("", "Lưu không thành công, vui lòng đóng file trước khi lưu", custom_message_box::Error).exec();
        }
    }else{
        custom_message_box("", "Vui lòng chọn địa chỉ và nhập tên để lưu", custom_message_box::Error).exec();
    }
}

void MainWindow::on_export_to_hop_clicked(){
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     tr("Lưu file"), QDir::homePath(),
                                                     tr("Excel (*.xlsx)"));
    if (!file_name.isEmpty()){
        if(!exportToHopToExcel(file_name)){
            custom_message_box("", "Lưu không thành công, vui lòng đóng file trước khi lưu", custom_message_box::Error).exec();
        }
    }else{
        custom_message_box("", "Vui lòng chọn địa chỉ và nhập tên để lưu", custom_message_box::Error).exec();
    }
}

void MainWindow::on_export_ptxt_clicked(){
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     tr("Lưu file"), QDir::homePath(),
                                                     tr("Excel (*.xlsx)"));
    if (!file_name.isEmpty()){
        if(!exportPtxtToExcel(file_name)){
            custom_message_box("", "Lưu không thành công, vui lòng đóng file trước khi lưu", custom_message_box::Error).exec();
        }
    }else{
        custom_message_box("", "Vui lòng chọn địa chỉ và nhập tên để lưu", custom_message_box::Error).exec();
    }
}

void MainWindow::on_export_sat_clicked(){
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     tr("Lưu file"), QDir::homePath(),
                                                     tr("Excel (*.xlsx)"));
    if (!file_name.isEmpty()){
        if(!exportDiemSatToExcel(file_name)){
            custom_message_box("", "Lưu không thành công, vui lòng đóng file trước khi lưu", custom_message_box::Error).exec();
        }
    }else{
        custom_message_box("", "Vui lòng chọn địa chỉ và nhập tên để lưu", custom_message_box::Error).exec();
    }
}

void MainWindow::on_export_dkxt_clicked(){
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     tr("Lưu file"), QDir::homePath(),
                                                     tr("Excel (*.xlsx)"));
    if (!file_name.isEmpty()){
        if(!exportDKXTToExcel(file_name)){
            custom_message_box("", "Lưu không thành công, vui lòng đóng file trước khi lưu", custom_message_box::Error).exec();
        }
    }else{
        custom_message_box("", "Vui lòng chọn địa chỉ và nhập tên để lưu", custom_message_box::Error).exec();
    }
}

void MainWindow::on_export_hoc_ba_clicked(){
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     tr("Lưu file"), QDir::homePath(),
                                                     tr("Excel (*.xlsx)"));
    if (!file_name.isEmpty()){
        if(!exportHocBaToExcel(file_name)){
            custom_message_box("", "Lưu không thành công, vui lòng đóng file trước khi lưu", custom_message_box::Error).exec();
        }
    }else{
        custom_message_box("", "Vui lòng chọn địa chỉ và nhập tên để lưu", custom_message_box::Error).exec();
    }
}

void MainWindow::on_export_ccnn_clicked(){
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     tr("Lưu file"), QDir::homePath(),
                                                     tr("Excel (*.xlsx)"));
    if (!file_name.isEmpty()){
        if(!exportCCNNToExcel(file_name)){
            custom_message_box("", "Lưu không thành công, vui lòng đóng file trước khi lưu", custom_message_box::Error).exec();
        }
    }else{
        custom_message_box("", "Vui lòng chọn địa chỉ và nhập tên để lưu", custom_message_box::Error).exec();
    }
}

void MainWindow::on_export_doat_giai_clicked(){
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     tr("Lưu file"), QDir::homePath(),
                                                     tr("Excel (*.xlsx)"));
    if (!file_name.isEmpty()){
        if(!exportDoatGiaiToExcel(file_name)){
            custom_message_box("", "Lưu không thành công, vui lòng đóng file trước khi lưu", custom_message_box::Error).exec();
        }
    }else{
        custom_message_box("", "Vui lòng chọn địa chỉ và nhập tên để lưu", custom_message_box::Error).exec();
    }
}

void MainWindow::on_export_uutien_clicked(){
    QString file_name = QFileDialog::getSaveFileName(this,
                                                     tr("Lưu file"), QDir::homePath(),
                                                     tr("Excel (*.xlsx)"));
    if (!file_name.isEmpty()){
        if(!exportUuTienToExcel(file_name)){
            custom_message_box("", "Lưu không thành công, vui lòng đóng file trước khi lưu", custom_message_box::Error).exec();
        }
    }else{
        custom_message_box("", "Vui lòng chọn địa chỉ và nhập tên để lưu", custom_message_box::Error).exec();
    }
}

