#include "diem_hocba_dialog.h"
#include "ui_diem_hocba_dialog.h"

#include "db/diem_hocba_dao.h"
#include "db/monhoc_dao.h"
#include "ui/custom_message_box.h"

diem_hocba_dialog::diem_hocba_dialog(Type type, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::diem_hocba_dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    auto monhoc_list = getAllMonHoc();
    for (const auto &item : *monhoc_list){
        ui->mon_hoc->addItem(item->ten_monhoc, QVariant::fromValue(item->id_monhoc));
    }

    this->type = type;

    switch (this->type) {
    case Type::ADD:
        ui->accept->setText("Thêm");
        ui->title->setText("Thêm điểm học bạ");
        break;
    case Type::CHANGE:
        ui->accept->setText("Thay đổi");
        ui->title->setText("Thay đổi điểm học bạ");
        break;
    }
}

diem_hocba_dialog::~diem_hocba_dialog()
{
    delete ui;
}

void diem_hocba_dialog::setEditItem(diem_hocba_ptr &item){
    this->edit_item = item;
    ui->lop10->setValue(item->lop10);
    ui->lop11->setValue(item->lop11);
    ui->lop12->setValue(item->lop12);
    if (item->mon_hoc) {
        int index = ui->mon_hoc->findData(QVariant::fromValue(item->mon_hoc->id_monhoc));
        if (index >= 0) {
            ui->mon_hoc->setCurrentIndex(index);
        }
    }
}

void diem_hocba_dialog::on_accept_clicked(){
    float lop10 = ui->lop10->value();
    float lop11 = ui->lop11->value();
    float lop12 = ui->lop12->value();
    long id_mon_hoc = ui->mon_hoc->currentData().toLongLong();

    if (lop10 < 0.0f || lop11 < 0.0f || lop12 < 0.0f) {
        custom_message_box("", "Điểm không thể âm", custom_message_box::Error).exec();
        return;
    }

    if (id_mon_hoc <= 0) {
        custom_message_box("", "Vui lòng chọn môn học", custom_message_box::Error).exec();
        return;
    }

    switch (this->type) {
    case Type::ADD:{

        if (!addDiemHocba(id_thi_sinh, id_mon_hoc, lop10, lop11, lop12)) {
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

        if (!changeDiemHocba(edit_item, id_mon_hoc, lop10, lop11, lop12)) {
            custom_message_box("", "Cập nhật thất bại", custom_message_box::Error).exec();
        } else {
            custom_message_box("", "Cập nhật thành công", custom_message_box::Information).exec();
            accept();
        }
    }
    break;
    }
}

void diem_hocba_dialog::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void diem_hocba_dialog::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void diem_hocba_dialog::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}

void diem_hocba_dialog::on_close_clicked(){
    reject();
}

void diem_hocba_dialog::on_cancel_clicked(){
    reject();
}
