#include "uutien_dialog.h"
#include "ui_uutien_dialog.h"

#include "db/ma_dtut_dao.h"
#include "db/ma_kvut_dao.h"
#include "db/uutien_dao.h"
#include "ui/custom_message_box.h"

uutien_dialog::uutien_dialog(Type type, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::uutien_dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    this->type = type;
    switch (this->type) {
    case Type::ADD:
        ui->accept->setText("Thêm");
        ui->title->setText("Thêm ưu tiên");
        break;
    case Type::CHANGE:
        ui->accept->setText("Thay đổi");
        ui->title->setText("Thay đổi ưu tiên");
        break;
    }

    // populate dtut
    auto dtut_list = getAllMaDtut();
    ui->dtut->addItem("", QVariant());
    if (dtut_list) {
        for (auto &d : *dtut_list) {
            ui->dtut->addItem(d->ma, QVariant::fromValue(d->id));
        }
    }

    // populate kvut
    auto kvut_list = getAllMaKvut();
    ui->kvut->addItem("", QVariant());
    if (kvut_list) {
        for (auto &k : *kvut_list) {
            ui->kvut->addItem(k->ma, QVariant::fromValue(k->id));
        }
    }
}

uutien_dialog::~uutien_dialog()
{
    delete ui;
}

void uutien_dialog::setEditItem(uutien_ptr &item){
    this->edit_item = item;
    if (item->dtut) {
        for (int i = 0; i < ui->dtut->count(); ++i) {
            if (ui->dtut->itemData(i).toLongLong() == item->dtut->id) {
                ui->dtut->setCurrentIndex(i);
                break;
            }
        }
    }
    if (item->kvut) {
        for (int i = 0; i < ui->kvut->count(); ++i) {
            if (ui->kvut->itemData(i).toLongLong() == item->kvut->id) {
                ui->kvut->setCurrentIndex(i);
                break;
            }
        }
    }
}

void uutien_dialog::on_accept_clicked(){
    long id_dtut = ui->dtut->currentData().toLongLong();
    long id_kvut = ui->kvut->currentData().toLongLong();

    switch (this->type) {
    case Type::ADD: {
        if (!addUuTien(id_thi_sinh, id_dtut, id_kvut)) {
            custom_message_box("", "Thêm thất bại", custom_message_box::Error).exec();
        } else {
            accept();
        }
    }
        break;
    case Type::CHANGE: {
        if (!edit_item) {
            custom_message_box("", "Item null", custom_message_box::Error).exec();
            return;
        }
        if (!changeUuTien(edit_item, id_thi_sinh, id_dtut, id_kvut)) {
            custom_message_box("", "Cập nhật thất bại", custom_message_box::Error).exec();
        } else {
            accept();
        }
    }
        break;
    }
}

void uutien_dialog::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void uutien_dialog::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void uutien_dialog::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}

void uutien_dialog::on_close_clicked(){
    reject();
}

void uutien_dialog::on_cancel_clicked(){
    reject();
}
