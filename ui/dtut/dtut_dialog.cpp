#include "dtut_dialog.h"
#include "ui_dtut_dialog.h"

#include "db/ma_dtut_dao.h"
#include "ui/custom_message_box.h"

dtut_dialog::dtut_dialog(Type type, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dtut_dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    this->type = type;
    switch (this->type) {
    case Type::ADD:
        ui->accept->setText("Thêm");
        ui->title->setText("Thêm điểm ưu tiên");
        break;
    case Type::CHANGE:
        ui->accept->setText("Thay đổi");
        ui->title->setText("Thay đổi điểm ưu tiên");
        break;
    }
}

dtut_dialog::~dtut_dialog()
{
    delete ui;
}

void dtut_dialog::setEditItem(ma_dtut_ptr &item){
    this->edit_item = item;
    ui->ma->setText(item->ma);
    ui->ten->setText(item->ten);
    ui->diem->setValue(item->diem);
}

void dtut_dialog::on_accept_clicked(){
    QString ma = ui->ma->text();
    QString ten = ui->ten->text();
    float diem = static_cast<float>(ui->diem->value());

    switch (this->type) {
    case Type::ADD: {
        if (!addMaDtut(ma, ten, diem)) {
            custom_message_box("", "Thêm thất bại", custom_message_box::Error).exec();
        } else {
            custom_message_box("", "Thêm thành công", custom_message_box::Information).exec();
            accept();
        }
    }
        break;
    case Type::CHANGE: {
        if (!edit_item) {
            custom_message_box("", "Item null", custom_message_box::Error).exec();
            return;
        }
        if (!changeMaDtut(edit_item, ma, ten, diem)) {
            custom_message_box("", "Cập nhật thất bại", custom_message_box::Error).exec();
        } else {
            custom_message_box("", "Cập nhật thành công", custom_message_box::Information).exec();
            accept();
        }
    }
        break;
    }
}

void dtut_dialog::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void dtut_dialog::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void dtut_dialog::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}

void dtut_dialog::on_close_clicked(){
    reject();
}

void dtut_dialog::on_cancel_clicked(){
    reject();
}
