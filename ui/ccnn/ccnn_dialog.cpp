#include "ccnn_dialog.h"
#include "ui_ccnn_dialog.h"

#include "db/ma_chungchinn_dao.h"
#include "ui/custom_message_box.h"

ccnn_dialog::ccnn_dialog(Type type, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ccnn_dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    this->type = type;
    switch (this->type) {
    case Type::ADD:
        ui->accept->setText("Thêm");
        ui->title->setText("Thêm chứng chỉ");
        break;
    case Type::CHANGE:
        ui->accept->setText("Thay đổi");
        ui->title->setText("Thay đổi chứng chỉ");
        break;
    }
}

ccnn_dialog::~ccnn_dialog()
{
    delete ui;
}

void ccnn_dialog::setEditItem(ma_chungchinn_ptr &item){
    this->edit_item = item;
    ui->ma->setText(item->ma);
    ui->ten->setText(item->ten);
}

void ccnn_dialog::on_accept_clicked(){
    QString ma = ui->ma->text();
    QString ten = ui->ten->text();

    switch (this->type) {
    case Type::ADD: {
        if (!addMaChungchinn(ma, ten)) {
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
        if (!changeMaChungchinn(edit_item, ma, ten)) {
            custom_message_box("", "Cập nhật thất bại", custom_message_box::Error).exec();
        } else {
            custom_message_box("", "Cập nhật thành công", custom_message_box::Information).exec();
            accept();
        }
    }
        break;
    }
}

void ccnn_dialog::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void ccnn_dialog::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void ccnn_dialog::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}

void ccnn_dialog::on_close_clicked(){
    reject();
}

void ccnn_dialog::on_cancel_clicked(){
    reject();
}
