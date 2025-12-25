#include "chungchi_tienganh_dialog.h"
#include "ui_chungchi_tienganh_dialog.h"

#include "db/chungchi_tienganh_dao.h"
#include "db/ma_chungchinn_dao.h"
#include "db/ptxt_dao.h"
#include "ui/custom_message_box.h"

chungchi_tienganh_dialog::chungchi_tienganh_dialog(Type type, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::chungchi_tienganh_dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    auto ccnn_list = getAllMaChungchinn();
    for (const auto &item : *ccnn_list){
        ui->ccnn->addItem(item->ten, QVariant::fromValue(item->id));
    }

    auto ptxt_list = getAllPtxt();
    ui->ptxt->addItem("", NULL);
    for (const auto &item : *ptxt_list){
        ui->ptxt->addItem(item->ten, QVariant::fromValue(item->id));
    }

    this->type = type;

    switch (this->type) {
    case Type::ADD:
        ui->accept->setText("Thêm");
        ui->title->setText("Thêm chứng chỉ tiếng Anh");
        break;
    case Type::CHANGE:
        ui->accept->setText("Thay đổi");
        ui->title->setText("Thay đổi chứng chỉ tiếng Anh");
        break;
    }
}

chungchi_tienganh_dialog::~chungchi_tienganh_dialog()
{
    delete ui;
}

void chungchi_tienganh_dialog::setEditItem(chungchi_tienganh_ptr &item){
    this->edit_item = item;
    ui->diem->setValue(item->diem);

    int index = ui->ccnn->findData(QVariant::fromValue(item->ccnn->id));
    ui->ccnn->setCurrentIndex(index);

    index = ui->ptxt->findData(QVariant::fromValue(item->ptxt->id));
    ui->ptxt->setCurrentIndex(index);
}

void chungchi_tienganh_dialog::on_accept_clicked(){
    float diem = ui->diem->value();
    long id_ccnn = ui->ccnn->currentData().toLongLong();
    long id_ptxt = ui->ptxt->currentData().toLongLong();
    switch (this->type) {
    case Type::ADD:{
        if (!addChungchiTienganh(id_thi_sinh, id_ccnn, diem, id_ptxt)) {
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

        if (!changeChungchiTienganh(edit_item,  id_ccnn, diem, id_ptxt)) {
            custom_message_box("", "Cập nhật thất bại", custom_message_box::Error).exec();
        } else {
            custom_message_box("", "Cập nhật thành công", custom_message_box::Information).exec();
            accept();
        }
    }
    break;
    }
}

void chungchi_tienganh_dialog::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void chungchi_tienganh_dialog::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void chungchi_tienganh_dialog::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}

void chungchi_tienganh_dialog::on_close_clicked(){
    reject();
}

void chungchi_tienganh_dialog::on_cancel_clicked(){
    reject();
}
