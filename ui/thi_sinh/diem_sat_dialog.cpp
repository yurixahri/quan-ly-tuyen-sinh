#include "diem_sat_dialog.h"
#include "ui_diem_sat_dialog.h"

#include "db/diem_thi_sat_dao.h"
#include "db/ptxt_dao.h"
#include "ui/custom_message_box.h"

diem_sat_dialog::diem_sat_dialog(Type type, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::diem_sat_dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    auto ptxt_list = getAllPtxt();
    ui->ptxt->addItem("", QVariant());
    for (const auto &item : *ptxt_list){
        ui->ptxt->addItem(item->ten, QVariant::fromValue(item->id));
    }

    this->type = type;

    switch (this->type) {
    case Type::ADD:
        ui->accept->setText("Thêm");
        ui->title->setText("Thêm điểm SAT");
        break;
    case Type::CHANGE:
        ui->accept->setText("Thay đổi");
        ui->title->setText("Thay đổi điểm SAT");
        break;
    }
}

diem_sat_dialog::~diem_sat_dialog()
{
    delete ui;
}

void diem_sat_dialog::setEditItem(diem_thi_sat_ptr &item){
    this->edit_item = item;
    ui->diem->setValue(item->diem);
    ui->ma_dvtctdl->setText(item->ma_dvtctdl);
    ui->ten_dvtctdl->setText(item->ten_dvtctdl);

    int index = ui->ptxt->findData(QVariant::fromValue(item->ptxt->id));
    ui->ptxt->setCurrentIndex(index);
}

void diem_sat_dialog::on_accept_clicked(){
    float diem = ui->diem->value();
    QString ma_dvtctdl = ui->ma_dvtctdl->text().trimmed();
    QString ten_dvtctdl = ui->ten_dvtctdl->text().trimmed();
    long id_ptxt = ui->ptxt->currentData().toLongLong();

    if (ma_dvtctdl.isEmpty() || ten_dvtctdl.isEmpty()) {
        custom_message_box("", "Vui lòng điền đầy đủ thông tin", custom_message_box::Error).exec();
        return;
    }

    switch (this->type) {
    case Type::ADD:{

        if (!addDiemThiSat(id_thi_sinh, id_ptxt, diem, ma_dvtctdl, ten_dvtctdl)) {
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

        if (!changeDiemThiSat(edit_item, id_ptxt, diem, ma_dvtctdl, ten_dvtctdl)) {
            custom_message_box("", "Cập nhật thất bại", custom_message_box::Error).exec();
        } else {
            custom_message_box("", "Cập nhật thành công", custom_message_box::Information).exec();
            accept();
        }
    }
    break;
    }
}

void diem_sat_dialog::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void diem_sat_dialog::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void diem_sat_dialog::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}

void diem_sat_dialog::on_close_clicked(){
    reject();
}

void diem_sat_dialog::on_cancel_clicked(){
    reject();
}
