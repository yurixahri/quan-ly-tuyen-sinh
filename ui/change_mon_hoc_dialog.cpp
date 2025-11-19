#include "change_mon_hoc_dialog.h"
#include "ui_change_mon_hoc_dialog.h"

#include <QSqlError>
#include "ui/custom_message_box.h"

change_mon_hoc_dialog::change_mon_hoc_dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::change_mon_hoc_dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
}

change_mon_hoc_dialog::~change_mon_hoc_dialog(){
    delete ui;
}

void change_mon_hoc_dialog::on_cancel_clicked(){
    reject();
}

void change_mon_hoc_dialog::on_close_clicked(){
    reject();
}


void change_mon_hoc_dialog::on_accept_clicked(){
    if (!mon_hoc) {
        custom_message_box("", "Môn học null", custom_message_box::Error).exec();
        return;
    }
    mon_hoc->ten_monhoc = ui->ten_monhoc->text();
    QSqlError err = qx::dao::update(mon_hoc);

    if (err.isValid()) {
        custom_message_box("", err.text(), custom_message_box::Error).exec();
    } else {
        custom_message_box("", "Cập nhật thành công", custom_message_box::Information).exec();
        accept();
    }
}

void change_mon_hoc_dialog::setMonHoc(mon_hoc_ptr &mon_hoc){
    this->mon_hoc = mon_hoc;
    ui->id->setText(QString::number(mon_hoc->id_monhoc));
    ui->ten_monhoc->setText(mon_hoc->ten_monhoc);
}


void change_mon_hoc_dialog::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void change_mon_hoc_dialog::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void change_mon_hoc_dialog::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}
