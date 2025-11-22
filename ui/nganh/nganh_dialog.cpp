#include "nganh_dialog.h"
#include "ui_nganh_dialog.h"
#include "db/nhom_nganh_dao.h"
#include "ui/custom_message_box.h"

nganh_dialog::nganh_dialog(Type type, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::nganh_dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    this->type = type;

    switch (this->type) {
    case Type::ADD:
        ui->accept->setText("Thêm");
        ui->title->setText("Thêm ngành");
        break;
    case Type::CHANGE:
        ui->accept->setText("Thay đổi");
        ui->title->setText("Thay đổi ngành");
        break;
    }

    auto nhom_nganh_list = getAllNhomNganh();
    for (const auto &nhom_nganh : *nhom_nganh_list){
        ui->nhom_nganh->addItem(nhom_nganh->ten, QVariant::fromValue(nhom_nganh->id_nhom_nganh));
    }
}

nganh_dialog::~nganh_dialog(){
    delete ui;
}

void nganh_dialog::setEditItem(nganh_ptr &item){
    this->edit_item = item;
    ui->ma->setText(item->ma_nganh);
    ui->ten->setText(item->ten_nganh);

    int index = ui->nhom_nganh->findData(QVariant::fromValue(item->nhom_nganh->id_nhom_nganh));
    ui->nhom_nganh->setCurrentIndex(index);

}

void nganh_dialog::on_accept_clicked(){
    QString ma = ui->ma->text();
    QString ten = ui->ten->text();
    long id_nhom_nganh = ui->nhom_nganh->currentData().toLongLong();

    switch (this->type) {
    case Type::ADD:{
        if (!addNganh(ma, ten, id_nhom_nganh)) custom_message_box("", "Thêm thất bại", custom_message_box::Error).exec();
        else accept();
    }
    break;
    case Type::CHANGE:{
        if (!edit_item) {
            custom_message_box("", "Item null", custom_message_box::Error).exec();
            return;
        }
        edit_item->ma_nganh = ma;
        edit_item->ten_nganh = ten;
        edit_item->nhom_nganh = std::make_shared<nhom_nganh>(id_nhom_nganh);
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

void nganh_dialog::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void nganh_dialog::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void nganh_dialog::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}

void nganh_dialog::on_cancel_clicked(){
    reject();
}

void nganh_dialog::on_close_clicked(){
    reject();
}

