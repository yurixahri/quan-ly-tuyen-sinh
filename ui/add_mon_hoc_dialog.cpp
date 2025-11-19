#include "add_mon_hoc_dialog.h"
#include "ui_add_mon_hoc_dialog.h"
#include "db/monhoc_dao.h"
#include "custom_message_box.h"

add_mon_hoc_dialog::add_mon_hoc_dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::add_mon_hoc_dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
}

add_mon_hoc_dialog::~add_mon_hoc_dialog(){
    delete ui;
}

void add_mon_hoc_dialog::on_accept_clicked(){
    QString ten = ui->ten_monhoc->text();

    if (!addMonHoc(ten)) custom_message_box("", "Thêm thất bại, tên môn học có thể đã tồn tại hoặc để tróng", custom_message_box::Error).exec();
    else accept();
}

void add_mon_hoc_dialog::on_close_clicked(){
    reject();
}

void add_mon_hoc_dialog::on_cancel_clicked(){
    reject();
}

void add_mon_hoc_dialog::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void add_mon_hoc_dialog::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void add_mon_hoc_dialog::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}


