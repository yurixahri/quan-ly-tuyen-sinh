#include "ma_nganh_dialog.h"
#include "ui_ma_nganh_dialog.h"
#include "db/ma_nganh_dao.h"
#include "db/nganh_dao.h"
#include "db/tohop_dao.h"
#include "db/ptxt_dao.h"
#include "ui/custom_message_box.h"

ma_nganh_dialog::ma_nganh_dialog(Type type,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ma_nganh_dialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    this->type = type;
    update();
}

ma_nganh_dialog::~ma_nganh_dialog(){
    delete ui;
}

void ma_nganh_dialog::setEditItem(ma_nganh_ptr &item){
    this->edit_item = item;
    ui->nganh->addItem(item->nganh->ma_nganh, QVariant::fromValue(item->nganh->id));
    ui->chi_tieu->setValue(item->chi_tieu);
    ui->ghi_chu->setText(item->ghi_chu);

    QList<QVariant> list_tohop;
    QList<QVariant> list_ptxt;

    for (auto &tohop : item->list_tohop)
        list_tohop.append(QVariant::fromValue(tohop->tohop->id_tohop));
    for (auto &ptxt : item->list_ptxt)
        list_ptxt.append(QVariant::fromValue(ptxt->ptxt->id));

    ui->tohop->setSelectedValues(list_tohop);
    ui->ptxt->setSelectedValues(list_ptxt);
}

void ma_nganh_dialog::update(){
    auto list_tohop = getAllToHop();
    for (auto &tohop : *list_tohop){
        ui->tohop->addItem(tohop->ma_tohop, QVariant::fromValue(tohop->id_tohop));
    }
    auto list_ptxt = getAllPtxt();
    for (auto &ptxt : *list_ptxt){
        ui->ptxt->addItem(ptxt->ma, QVariant::fromValue(ptxt->id));
    }

    if (type == Type::CHANGE) {
        ui->nganh->setEnabled(false);
    }else{
        auto list_nganh = getAllNganh();
        for (auto &nganh : *list_nganh){
            ui->nganh->addItem(nganh->ma_nganh, QVariant::fromValue(nganh->id));
        }
    }
}

void ma_nganh_dialog::on_accept_clicked(){
    int chi_tieu = ui->chi_tieu->value();
    QString ghi_chu = ui->ghi_chu->text();
    long id_nganh = ui->nganh->currentData().toLongLong();
    QList<QVariant> list_tohop = ui->tohop->currentValues();
    QList<QVariant> list_ptxt = ui->ptxt->currentValues();

    switch (this->type) {
    case Type::ADD:{
        if (!addMaNganh(id_nganh, list_tohop, list_ptxt, chi_tieu, ghi_chu)) custom_message_box("", "Thêm thất bại", custom_message_box::Error).exec();
        else accept();
    }
    break;
    case Type::CHANGE:{
        if (!changeMaNganh(edit_item, list_tohop, list_ptxt, chi_tieu, ghi_chu)) custom_message_box("", "Thay đổi thất bại", custom_message_box::Error).exec();
        else accept();
    }
    break;
    }
}


void ma_nganh_dialog::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void ma_nganh_dialog::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void ma_nganh_dialog::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}

void ma_nganh_dialog::on_cancel_clicked(){
    reject();
}

void ma_nganh_dialog::on_close_clicked(){
    reject();
}

