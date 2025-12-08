#include "ptxt_dialog.h"
#include "ui_ptxt_dialog.h"
#include "db/ptxt_dao.h"
#include "ui/custom_message_box.h"

ptxt_dialog::ptxt_dialog(Type type, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ptxt_dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    this->type = type;

    switch (this->type) {
    case Type::ADD:
        ui->accept->setText("Thêm");
        ui->title->setText("Thêm phương thức xét tuyển");
        break;
    case Type::CHANGE:
        ui->accept->setText("Thay đổi");
        ui->title->setText("Thay phương thức xét tuyển");
        break;
    }
}

ptxt_dialog::~ptxt_dialog(){
    delete ui;
}

void ptxt_dialog::setEditItem(ptxt_ptr &item){
    this->edit_item = item;
    ui->ma->setText(item->ma);
    ui->ten->setText(item->ten);
    ui->thang_diem->setValue(item->thang_diem);
    ui->mo_ta->setText(item->mo_ta);
}

void ptxt_dialog::on_accept_clicked(){
    QString ma = ui->ma->text();
    QString ten = ui->ten->text();
    float thang_diem = ui->thang_diem->value();
    QString mo_ta = ui->mo_ta->text();

    switch (this->type) {
    case Type::ADD:{
        if (!addPtxt(ma, ten, thang_diem, mo_ta)) custom_message_box("", "Thêm thất bại", custom_message_box::Error).exec();
        else accept();
    }
    break;
    case Type::CHANGE:{
        if (!edit_item) {
            custom_message_box("", "Item null", custom_message_box::Error).exec();
            return;
        }

        if (!changePtxt(edit_item, ma, ten, thang_diem,mo_ta)) {
            custom_message_box("", "Cập nhật thất bại", custom_message_box::Error).exec();
        } else {
            custom_message_box("", "Cập nhật thành công", custom_message_box::Information).exec();
            accept();
        }
    }
    break;
    }
}

void ptxt_dialog::on_close_clicked(){
    reject();
}

void ptxt_dialog::on_cancel_clicked(){
    reject();
}

void ptxt_dialog::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void ptxt_dialog::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void ptxt_dialog::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}


