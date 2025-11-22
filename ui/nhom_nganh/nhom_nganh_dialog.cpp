#include "nhom_nganh_dialog.h"
#include "ui_nhom_nganh_dialog.h"
#include "db/nhom_nganh_dao.h"
#include "ui/custom_message_box.h"

nhom_nganh_dialog::nhom_nganh_dialog(Type type, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::nhom_nganh_dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    this->type = type;

    switch (this->type) {
    case Type::ADD:
        ui->accept->setText("Thêm");
        ui->title->setText("Thêm nhóm ngành");
        break;
    case Type::CHANGE:
        ui->accept->setText("Thay đổi");
        ui->title->setText("Thay đổi nhóm ngành");
        break;
    }
}

nhom_nganh_dialog::~nhom_nganh_dialog()
{
    delete ui;
}

void nhom_nganh_dialog::setEditItem(nhom_nganh_ptr &item){
    this->edit_item = item;
    ui->ten_nhom_nganh->setText(item->ten);
}

void nhom_nganh_dialog::on_accept_clicked(){
    QString ten = ui->ten_nhom_nganh->text();
    qDebug() << ten;
    switch (this->type) {
    case Type::ADD:{
        if (!addNhomNganh(ten)) custom_message_box("", "Thêm thất bại", custom_message_box::Error).exec();
        else accept();
    }
    break;
    case Type::CHANGE:{
        if (!edit_item) {
            custom_message_box("", "Item null", custom_message_box::Error).exec();
            return;
        }
        edit_item->ten = ten;
        QSqlError err = qx::dao::update(edit_item);

        if (err.isValid()) {
            custom_message_box("", err.text(), custom_message_box::Error).exec();
        } else {
            custom_message_box("", "Cập nhật thành công", custom_message_box::Information).exec();
            accept();
        }
    }
    break;
    }
}

void nhom_nganh_dialog::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void nhom_nganh_dialog::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void nhom_nganh_dialog::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}

void nhom_nganh_dialog::on_cancel_clicked(){
    reject();
}


void nhom_nganh_dialog::on_close_clicked(){
    reject();
}

