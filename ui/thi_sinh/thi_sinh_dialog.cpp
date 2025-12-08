#include "thi_sinh_dialog.h"
#include "ui_thi_sinh_dialog.h"

#include "db/thi_sinh_dao.h"
#include "ui/custom_message_box.h"

thi_sinh_dialog::thi_sinh_dialog(Type type, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::thi_sinh_dialog)
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

thi_sinh_dialog::~thi_sinh_dialog()
{
    delete ui;
}

void thi_sinh_dialog::setEditItem(thi_sinh_ptr &item){
    this->edit_item = item;
    ui->cccd->setText(item->cccd);
    ui->ho_ten->setText(item->ho_ten);
    ui->ngay_sinh->setDate(item->ngay_sinh);
    ui->gioi_tinh->setCurrentText(item->gioi_tinh);
    ui->dia_chi->setText(item->dia_chi);
    ui->email->setText(item->email);
    ui->sdt->setText(item->sdt);
    ui->ma_dinh_danh->setText(item->ma_dinh_danh);
}

void thi_sinh_dialog::on_accept_clicked(){
    QString cccd = ui->cccd->text();
    QString ho_ten = ui->ho_ten->text();
    QDate ngay_sinh = ui->ngay_sinh->date();
    QString gioi_tinh = ui->gioi_tinh->currentText();
    QString dia_chi = ui->dia_chi->text();
    QString email = ui->email->text();
    QString sdt = ui->sdt->text();
    QString ma_dinh_danh = ui->ma_dinh_danh->text();

    switch (this->type) {
    case Type::ADD:{
        if (!addThiSinh(cccd, ho_ten, ngay_sinh, gioi_tinh, dia_chi, email, sdt, ma_dinh_danh)) custom_message_box("", "Thêm thất bại, ", custom_message_box::Error).exec();
        else accept();
    }
    break;
    case Type::CHANGE:{
        if (!edit_item) {
            custom_message_box("", "Item null", custom_message_box::Error).exec();
            return;
        }

        if (!changeThiSinh(edit_item, cccd, ho_ten, ngay_sinh, gioi_tinh, dia_chi, email, sdt, ma_dinh_danh)) {
            custom_message_box("", "Cập nhật thất bại", custom_message_box::Error).exec();
        } else {
            custom_message_box("", "Cập nhật thành công", custom_message_box::Information).exec();
            accept();
        }
    }
    break;
    }


}

void thi_sinh_dialog::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void thi_sinh_dialog::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void thi_sinh_dialog::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}

void thi_sinh_dialog::on_close_clicked(){
    reject();
}


void thi_sinh_dialog::on_cancel_clicked(){
    reject();
}
