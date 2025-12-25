#include "doat_giai_dialog.h"
#include "ui_doat_giai_dialog.h"

#include "db/doat_giai_dao.h"
#include "db/ma_thanhtich_dao.h"
#include "db/monhoc_dao.h"
#include "db/ptxt_dao.h"
#include "ui/custom_message_box.h"

doat_giai_dialog::doat_giai_dialog(Type type, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::doat_giai_dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    loadMonHoc();
    loadPtxt();
    loadMaThanhTich();

    this->type = type;

    switch (this->type) {
    case Type::ADD:
        ui->accept->setText("Thêm");
        ui->title->setText("Thêm đạt giải");
        break;
    case Type::CHANGE:
        ui->accept->setText("Thay đổi");
        ui->title->setText("Thay đổi đạt giải");
        break;
    }
}

doat_giai_dialog::~doat_giai_dialog()
{
    delete ui;
}

void doat_giai_dialog::loadMonHoc(){
    auto list = getAllMonHoc();
    if (list) {
        ui->mon_hoc->clear();
        ui->mon_hoc->addItem("", QVariant());
        for (auto &item : *list) {
            ui->mon_hoc->addItem(item->ten_monhoc, QVariant::fromValue(item->id_monhoc));
        }
    }
}

void doat_giai_dialog::loadMaThanhTich(){
    auto list = getAllMaThanhTich();
    if (list) {
        ui->thanh_tich->clear();
        ui->thanh_tich->addItem("", QVariant());
        for (auto &item : *list) {
            ui->thanh_tich->addItem(item->ma, QVariant::fromValue(item->id));
        }
    }
}

void doat_giai_dialog::loadPtxt(){
    auto list = getAllPtxt();
    if (list) {
        ui->ptxt->clear();
        ui->ptxt->addItem("", QVariant());
        for (auto &item : *list) {
            ui->ptxt->addItem(item->ma, QVariant::fromValue(item->id));
        }
    }
}

void doat_giai_dialog::setEditItem(doat_giai_ptr &item){
    this->edit_item = item;
    ui->diem->setValue(item->diem_thanh_tich);

    if (item->mon_hoc) {
        int index = ui->mon_hoc->findData(QVariant::fromValue(item->mon_hoc->id_monhoc));
        if (index >= 0) {
            ui->mon_hoc->setCurrentIndex(index);
        }
    }

    if (item->thanh_tich) {
        int index = ui->thanh_tich->findData(QVariant::fromValue(item->thanh_tich->id));
        if (index >= 0) {
            ui->thanh_tich->setCurrentIndex(index);
        }
    }

    if (item->ptxt) {
        int index = ui->ptxt->findData(QVariant::fromValue(item->ptxt->id));
        if (index >= 0) {
            ui->ptxt->setCurrentIndex(index);
        }
    }
}

void doat_giai_dialog::on_accept_clicked(){
    long id_thanh_tich = ui->thanh_tich->currentData().toLongLong();
    int diem_thanh_tich = ui->diem->value();
    long id_monhoc = ui->mon_hoc->currentData().toLongLong();
    long id_ptxt = ui->ptxt->currentData().toLongLong();

    switch (this->type) {
    case Type::ADD:{
        if (!addDoatGiai(id_thi_sinh, id_monhoc, id_ptxt, id_thanh_tich, diem_thanh_tich)) {
            custom_message_box("", "Thêm thất bại", custom_message_box::Error).exec();
        } else {
            custom_message_box("", "Thêm thành công", custom_message_box::Information).exec();
            accept();
        }
    }
    break;
    case Type::CHANGE:{
        if (!edit_item) {
            custom_message_box("", "Item null", custom_message_box::Error).exec();
            return;
        }

        if (!changeDoatGiai(edit_item, id_monhoc, id_ptxt, id_thanh_tich, diem_thanh_tich)) {
            custom_message_box("", "Cập nhật thất bại", custom_message_box::Error).exec();
        } else {
            custom_message_box("", "Cập nhật thành công", custom_message_box::Information).exec();
            accept();
        }
    }
    break;
    }
}

void doat_giai_dialog::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void doat_giai_dialog::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void doat_giai_dialog::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}

void doat_giai_dialog::on_close_clicked(){
    reject();
}

void doat_giai_dialog::on_cancel_clicked(){
    reject();
}
