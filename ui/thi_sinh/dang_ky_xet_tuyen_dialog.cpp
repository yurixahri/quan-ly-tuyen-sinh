#include "dang_ky_xet_tuyen_dialog.h"
#include "ui_dang_ky_xet_tuyen_dialog.h"

#include "db/dang_ky_xet_tuyen_dao.h"
#include "db/ma_nganh_dao.h"
#include "db/ptxt_dao.h"
#include "ui/custom_message_box.h"

dang_ky_xet_tuyen_dialog::dang_ky_xet_tuyen_dialog(Type type, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dang_ky_xet_tuyen_dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    this->type = type;

    switch (this->type) {
    case Type::ADD:
        ui->accept->setText("Thêm");
        ui->title->setText("Thêm đăng ký xét tuyển");
        loadMaNganh();
        loadPtxt();
        break;
    case Type::CHANGE:
        ui->accept->setText("Thay đổi");
        ui->title->setText("Thay đổi đăng ký xét tuyển");
        loadMaNganh();
        loadPtxt();
        ui->ma_nganh->setEnabled(false);  // can't change ma_nganh (part of composite key)
        break;
    }
}

dang_ky_xet_tuyen_dialog::~dang_ky_xet_tuyen_dialog()
{
    delete ui;
}

void dang_ky_xet_tuyen_dialog::loadMaNganh(){
    auto list = getAllMaNganh();
    if (list) {
        ui->ma_nganh->clear();
        for (auto &item : *list) {
            QString displayText = item->nganh->ma_nganh + " - " + item->nganh->ten_nganh;
            ui->ma_nganh->addItem(displayText, QVariant::fromValue(item->id));
        }
    }
}

void dang_ky_xet_tuyen_dialog::loadPtxt(){
    auto list = getAllPtxt();
    if (list) {
        ui->ptxt->clear();
        for (auto &item : *list) {
            ui->ptxt->addItem(item->ma, QVariant::fromValue(item->id));
        }
    }
}

void dang_ky_xet_tuyen_dialog::setEditItem(dang_ky_xet_tuyen_ptr &item){
    this->edit_item = item;

    // Set ma_nganh (read-only in CHANGE mode)
    if (item->ma_nganh) {
        int index = ui->ma_nganh->findData(QVariant::fromValue(item->ma_nganh->id));
        if (index >= 0) {
            ui->ma_nganh->setCurrentIndex(index);
        }
    }

    // Set ptxt
    if (item->ptxt) {
        int index = ui->ptxt->findData(QVariant::fromValue(item->ptxt->id));
        if (index >= 0) {
            ui->ptxt->setCurrentIndex(index);
        }
    }

    // Set diem and trang_thai
    ui->diem->setValue(static_cast<int>(item->diem));
    ui->lineEdit->setText(item->trang_thai);
}

void dang_ky_xet_tuyen_dialog::on_accept_clicked(){
    if (id_thi_sinh <= 0) {
        custom_message_box("", "Lỗi: Không có ID thí sinh", custom_message_box::Error).exec();
        return;
    }

    long id_ma_nganh = ui->ma_nganh->currentData().toLongLong();
    long id_ptxt = ui->ptxt->currentData().toLongLong();
    float diem = static_cast<float>(ui->diem->value());
    QString trang_thai = ui->lineEdit->text();

    if (id_ma_nganh <= 0) {
        custom_message_box("", "Vui lòng chọn mã ngành", custom_message_box::Error).exec();
        return;
    }

    switch (this->type) {
    case Type::ADD: {
        if (!addDangKyXetTuyen(id_thi_sinh, id_ma_nganh, id_ptxt, diem, trang_thai)) {
            custom_message_box("", "Thêm đăng ký xét tuyển thất bại", custom_message_box::Error).exec();
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

        if (!changeDangKyXetTuyen(edit_item, id_ptxt, diem, trang_thai)) {
            custom_message_box("", "Cập nhật đăng ký xét tuyển thất bại", custom_message_box::Error).exec();
        } else {
            accept();
        }
    }
    break;
    }
}

void dang_ky_xet_tuyen_dialog::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void dang_ky_xet_tuyen_dialog::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void dang_ky_xet_tuyen_dialog::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}

void dang_ky_xet_tuyen_dialog::on_close_clicked(){
    reject();
}

void dang_ky_xet_tuyen_dialog::on_cancel_clicked(){
    reject();
}
