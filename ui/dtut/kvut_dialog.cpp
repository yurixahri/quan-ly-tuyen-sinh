#include "kvut_dialog.h"
#include "ui_kvut_dialog.h"

#include "db/ma_kvut_dao.h"
#include "ui/custom_message_box.h"

kvut_dialog::kvut_dialog(Type type, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::kvut_dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    this->type = type;
    switch (this->type) {
    case Type::ADD:
        ui->accept->setText("Thêm");
        ui->title->setText("Thêm khu vực ưu tiên");
        break;
    case Type::CHANGE:
        ui->accept->setText("Thay đổi");
        ui->title->setText("Thay đổi khu vực ưu tiên");
        break;
    }
}

kvut_dialog::~kvut_dialog()
{
    delete ui;
}

void kvut_dialog::setEditItem(ma_kvut_ptr &item){
    this->edit_item = item;
    ui->ma->setText(item->ma);
    ui->ten->setText(item->ten);
    ui->diem->setValue(item->diem);
}

void kvut_dialog::on_accept_clicked(){
    QString ma = ui->ma->text();
    QString ten = ui->ten->text();
    float diem = static_cast<float>(ui->diem->value());

    switch (this->type) {
    case Type::ADD: {
        if (!addMaKvut(ma, ten, diem)) {
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
        if (!changeMaKvut(edit_item, ma, ten, diem)) {
            custom_message_box("", "Cập nhật thất bại", custom_message_box::Error).exec();
        } else {
            custom_message_box("", "Cập nhật thành công", custom_message_box::Information).exec();
            accept();
        }
    }
        break;
    }
}

void kvut_dialog::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void kvut_dialog::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void kvut_dialog::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}

void kvut_dialog::on_close_clicked(){
    reject();
}

void kvut_dialog::on_cancel_clicked(){
    reject();
}
