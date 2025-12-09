#include "thi_sinh_detail.h"
#include "ui_thi_sinh_detail.h"

#include "db/doat_giai_dao.h"
#include "db/diem_thi_sat_dao.h"
#include "db/diem_hocba_dao.h"
#include "db/chungchi_tienganh_dao.h"
#include "ui/custom_message_box.h"
#include "ui/thi_sinh/chungchi_tienganh_dialog.h"
#include "ui/thi_sinh/diem_hocba_dialog.h"
#include "ui/thi_sinh/diem_sat_dialog.h"
#include "ui/thi_sinh/doat_giai_dialog.h"

#include <QMenu>

thi_sinh_detail::thi_sinh_detail(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::thi_sinh_detail)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
}

thi_sinh_detail::~thi_sinh_detail()
{
    delete ui;
}


// ======== DOAT GIAI ========
void thi_sinh_detail::fillDoatGiaiTable(){
    auto list = getDoatGiaiByThiSinhId(item->id);
    if (!list) {
        qDebug() << "Error fetching doat_giai";
        return;
    }

    ui->thanh_tich_table->clearContents();
    ui->thanh_tich_table->setRowCount(0);
    ui->thanh_tich_table->setColumnCount(5);
    ui->thanh_tich_table->setHorizontalHeaderLabels({"ID", "Môn học", "Thành tích", "Điểm", "PTXT"});

    for (auto &item : *list) {
        int row = ui->thanh_tich_table->rowCount();
        ui->thanh_tich_table->insertRow(row);
        ui->thanh_tich_table->setItem(row, 0, new QTableWidgetItem(QString::number(item->id)));
        ui->thanh_tich_table->setItem(row, 1, new QTableWidgetItem(item->mon_hoc ? item->mon_hoc->ten_monhoc : ""));
        ui->thanh_tich_table->setItem(row, 2, new QTableWidgetItem(item->thanh_tich));
        ui->thanh_tich_table->setItem(row, 3, new QTableWidgetItem(QString::number(item->diem_thanh_tich)));
        ui->thanh_tich_table->setItem(row, 4, new QTableWidgetItem(item->ptxt ? item->ptxt->ma : ""));
    }

    ui->thanh_tich_table->setColumnHidden(0, true);
}

void thi_sinh_detail::on_add_thanh_tich_button_clicked(){
    doat_giai_dialog dlg(doat_giai_dialog::ADD, this);
    dlg.id_thi_sinh = item->id;

    if (dlg.exec() == QDialog::Accepted) {
        fillDoatGiaiTable();
    }
}

void thi_sinh_detail::on_thanh_tich_table_customContextMenuRequested(const QPoint &pos){
    QTableWidgetItem *item = ui->thanh_tich_table->itemAt(pos);

    if (item) {
        QMenu contextMenu(tr("Context Menu"), this);
        QAction *del = new QAction("Xóa", this);
        QAction *change = new QAction("Thay đổi", this);
        contextMenu.addAction(del);
        contextMenu.addAction(change);

        connect(change, &QAction::triggered, this, [=]() {
            updateDoatGiai(ui->thanh_tich_table->item(item->row(), 0)->text().toLong());
        });

        connect(del, &QAction::triggered, this, [=]() {
            deleteDoatGiai(ui->thanh_tich_table->item(item->row(), 0)->text().toLong());
        });

        contextMenu.exec(ui->thanh_tich_table->viewport()->mapToGlobal(pos));
    }
}

void thi_sinh_detail::updateDoatGiai(long id){
    auto doatGiai = getDoatGiaiById(id);
    if (doatGiai) {
        doat_giai_dialog dlg(doat_giai_dialog::CHANGE, this);
        dlg.id_thi_sinh = item->id;
        dlg.setEditItem(*doatGiai);

        if (dlg.exec() == QDialog::Accepted) {
            fillDoatGiaiTable();
        }
    }
}

void thi_sinh_detail::deleteDoatGiai(long id){
    custom_message_box confirm("", "Bạn có chắc muốn xóa đạt giải này?", custom_message_box::Question, true);
    if (confirm.exec() == QDialog::Accepted) {
        if (!deleteDoatGiaiById(id)) {
            custom_message_box("", "Xóa không thành công", custom_message_box::Error).exec();
        } else {
            custom_message_box("", "Xóa thành công", custom_message_box::Information).exec();
        }
        fillDoatGiaiTable();
    }
}

// ======== DIEM SAT ========
void thi_sinh_detail::fillDiemSatTable(){
    auto list = getDiemThiSatByThiSinhId(item->id);
    if (!list) {
        qDebug() << "Error fetching diem_sat";
        return;
    }

    ui->diem_sat_table->clearContents();
    ui->diem_sat_table->setRowCount(0);
    ui->diem_sat_table->setColumnCount(5);
    ui->diem_sat_table->setHorizontalHeaderLabels({"ID", "Điểm", "Mã DVTCTDL", "Tên DVTCTDL", "PTXT"});

    for (auto &item : *list) {
        int row = ui->diem_sat_table->rowCount();
        ui->diem_sat_table->insertRow(row);
        ui->diem_sat_table->setItem(row, 0, new QTableWidgetItem(QString::number(item->id)));
        ui->diem_sat_table->setItem(row, 1, new QTableWidgetItem(QString::number(item->diem)));
        ui->diem_sat_table->setItem(row, 2, new QTableWidgetItem(item->ma_dvtctdl));
        ui->diem_sat_table->setItem(row, 3, new QTableWidgetItem(item->ten_dvtctdl));
        ui->diem_sat_table->setItem(row, 4, new QTableWidgetItem(item->ptxt->ma));
    }

    ui->diem_sat_table->setColumnHidden(0, true);
}

void thi_sinh_detail::on_add_diem_sat_button_clicked(){
    diem_sat_dialog dlg(diem_sat_dialog::ADD, this);
    dlg.id_thi_sinh = item->id;

    if (dlg.exec() == QDialog::Accepted) {
        fillDiemSatTable();
    }
}

void thi_sinh_detail::on_diem_sat_table_customContextMenuRequested(const QPoint &pos){
    QTableWidgetItem *item = ui->diem_sat_table->itemAt(pos);

    if (item) {
        QMenu contextMenu(tr("Context Menu"), this);
        QAction *del = new QAction("Xóa", this);
        QAction *change = new QAction("Thay đổi", this);
        contextMenu.addAction(del);
        contextMenu.addAction(change);

        connect(change, &QAction::triggered, this, [=]() {
            updateDiemSat(ui->diem_sat_table->item(item->row(), 0)->text().toLong());
        });

        connect(del, &QAction::triggered, this, [=]() {
            deleteDiemSat(ui->diem_sat_table->item(item->row(), 0)->text().toLong());
        });

        contextMenu.exec(ui->diem_sat_table->viewport()->mapToGlobal(pos));
    }
}

void thi_sinh_detail::updateDiemSat(long id){
    auto diemSat = getDiemThiSatById(id);
    if (diemSat) {
        diem_sat_dialog dlg(diem_sat_dialog::CHANGE, this);
        dlg.id_thi_sinh = item->id;
        dlg.setEditItem(*diemSat);

        if (dlg.exec() == QDialog::Accepted) {
            fillDiemSatTable();
        }
    }
}

void thi_sinh_detail::deleteDiemSat(long id){
    custom_message_box confirm("", "Bạn có chắc muốn xóa điểm SAT này?", custom_message_box::Question, true);
    if (confirm.exec() == QDialog::Accepted) {
        if (!deleteDiemThiSatById(id)) {
            custom_message_box("", "Xóa không thành công", custom_message_box::Error).exec();
        } else {
            custom_message_box("", "Xóa thành công", custom_message_box::Information).exec();
        }
        fillDiemSatTable();
    }
}

// ======== DIEM HOCBA ========
void thi_sinh_detail::fillDiemHocbaTable(){
    auto list = getDiemHocbaByThiSinhId(item->id);
    if (!list) {
        qDebug() << "Error fetching diem_hocba";
        return;
    }

    ui->diem_hocba_table->clearContents();
    ui->diem_hocba_table->setRowCount(0);
    ui->diem_hocba_table->setColumnCount(5);
    ui->diem_hocba_table->setHorizontalHeaderLabels({"ID", "Môn học", "Lớp 10", "Lớp 11", "Lớp 12"});

    for (auto &item : *list) {
        int row = ui->diem_hocba_table->rowCount();
        ui->diem_hocba_table->insertRow(row);
        ui->diem_hocba_table->setItem(row, 0, new QTableWidgetItem(QString::number(item->id)));
        ui->diem_hocba_table->setItem(row, 1, new QTableWidgetItem(item->mon_hoc->ten_monhoc));
        ui->diem_hocba_table->setItem(row, 2, new QTableWidgetItem(QString::number(item->lop10)));
        ui->diem_hocba_table->setItem(row, 3, new QTableWidgetItem(QString::number(item->lop11)));
        ui->diem_hocba_table->setItem(row, 4, new QTableWidgetItem(QString::number(item->lop12)));
    }

    ui->diem_hocba_table->setColumnHidden(0, true);
}

void thi_sinh_detail::on_add_diem_hocba_button_clicked(){
    diem_hocba_dialog dlg(diem_hocba_dialog::ADD, this);
    dlg.id_thi_sinh = item->id;

    if (dlg.exec() == QDialog::Accepted) {
        fillDiemHocbaTable();
    }
}

void thi_sinh_detail::on_diem_hocba_table_customContextMenuRequested(const QPoint &pos){
    QTableWidgetItem *item = ui->diem_hocba_table->itemAt(pos);

    if (item) {
        QMenu contextMenu(tr("Context Menu"), this);
        QAction *del = new QAction("Xóa", this);
        QAction *change = new QAction("Thay đổi", this);
        contextMenu.addAction(del);
        contextMenu.addAction(change);

        connect(change, &QAction::triggered, this, [=]() {
            updateDiemHocba(ui->diem_hocba_table->item(item->row(), 0)->text().toLong());
        });

        connect(del, &QAction::triggered, this, [=]() {
            deleteDiemHocba(ui->diem_hocba_table->item(item->row(), 0)->text().toLong());
        });

        contextMenu.exec(ui->diem_hocba_table->viewport()->mapToGlobal(pos));
    }
}

void thi_sinh_detail::updateDiemHocba(long id){
    auto diemHocba = getDiemHocbaById(id);
    if (diemHocba) {
        diem_hocba_dialog dlg(diem_hocba_dialog::CHANGE, this);
        dlg.id_thi_sinh = item->id;
        dlg.setEditItem(*diemHocba);

        if (dlg.exec() == QDialog::Accepted) {
            fillDiemHocbaTable();
        }
    }
}

void thi_sinh_detail::deleteDiemHocba(long id){
    custom_message_box confirm("", "Bạn có chắc muốn xóa điểm học bạ này?", custom_message_box::Question, true);
    if (confirm.exec() == QDialog::Accepted) {
        if (!deleteDiemHocbaById(id)) {
            custom_message_box("", "Xóa không thành công", custom_message_box::Error).exec();
        } else {
            custom_message_box("", "Xóa thành công", custom_message_box::Information).exec();
        }
        fillDiemHocbaTable();
    }
}

// ======== CHUNGCHI TIENGANH ========
void thi_sinh_detail::fillChungchiTienganhTable(){
    auto list = getChungchiTienganhByThiSinhId(item->id);
    if (!list) {
        qDebug() << "Error fetching chungchi_tienganh";
        return;
    }

    ui->ccnn_table->clearContents();
    ui->ccnn_table->setRowCount(0);
    ui->ccnn_table->setColumnCount(4);
    ui->ccnn_table->setHorizontalHeaderLabels({"ID", "Chứng chỉ", "Điểm", "PTXT"});

    for (auto &item : *list) {
        int row = ui->ccnn_table->rowCount();
        ui->ccnn_table->insertRow(row);
        ui->ccnn_table->setItem(row, 0, new QTableWidgetItem(QString::number(item->id)));
        ui->ccnn_table->setItem(row, 1, new QTableWidgetItem(item->ccnn->ten));
        ui->ccnn_table->setItem(row, 2, new QTableWidgetItem(QString::number(item->diem)));
        ui->ccnn_table->setItem(row, 3, new QTableWidgetItem(item->ptxt->ma));
    }

    ui->ccnn_table->setColumnHidden(0, true);
}

void thi_sinh_detail::on_add_ccnn_button_clicked(){
    chungchi_tienganh_dialog dlg(chungchi_tienganh_dialog::ADD, this);
    dlg.id_thi_sinh = item->id;

    if (dlg.exec() == QDialog::Accepted) {
        fillChungchiTienganhTable();
    }
}

void thi_sinh_detail::on_ccnn_table_customContextMenuRequested(const QPoint &pos){
    QTableWidgetItem *item = ui->ccnn_table->itemAt(pos);

    if (item) {
        QMenu contextMenu(tr("Context Menu"), this);
        QAction *del = new QAction("Xóa", this);
        QAction *change = new QAction("Thay đổi", this);
        contextMenu.addAction(del);
        contextMenu.addAction(change);

        connect(change, &QAction::triggered, this, [=]() {
            updateChungchiTienganh(ui->ccnn_table->item(item->row(), 0)->text().toLong());
        });

        connect(del, &QAction::triggered, this, [=]() {
            deleteChungchiTienganh(ui->ccnn_table->item(item->row(), 0)->text().toLong());
        });

        contextMenu.exec(ui->ccnn_table->viewport()->mapToGlobal(pos));
    }
}

void thi_sinh_detail::updateChungchiTienganh(long id){
    auto chungchi = getChungchiTienganhById(id);
    if (chungchi) {
        chungchi_tienganh_dialog dlg(chungchi_tienganh_dialog::CHANGE, this);
        dlg.id_thi_sinh = item->id;
        dlg.setEditItem(*chungchi);

        if (dlg.exec() == QDialog::Accepted) {
            fillChungchiTienganhTable();
        }
    }
}

void thi_sinh_detail::deleteChungchiTienganh(long id){
    custom_message_box confirm("", "Bạn có chắc muốn xóa chứng chỉ này?", custom_message_box::Question, true);
    if (confirm.exec() == QDialog::Accepted) {
        if (!deleteChungchiTienganhById(id)) {
            custom_message_box("", "Xóa không thành công", custom_message_box::Error).exec();
        } else {
            custom_message_box("", "Xóa thành công", custom_message_box::Information).exec();
        }
        fillChungchiTienganhTable();
    }
}

void thi_sinh_detail::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void thi_sinh_detail::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void thi_sinh_detail::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}

void thi_sinh_detail::on_close_clicked(){
    reject();
}

void thi_sinh_detail::setThiSinh(thi_sinh_ptr item){
    this->item = item;
    fillDiemSatTable();
    fillDiemHocbaTable();
    fillChungchiTienganhTable();
    fillDoatGiaiTable();
}

