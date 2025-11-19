#include "add_tohop_dialog.h"
#include "ui_add_tohop_dialog.h"
#include "db/tohop_dao.h"
#include "db/monhoc_dao.h"
#include "ui/custom_message_box.h"
#include <QVariant>

add_tohop_dialog::add_tohop_dialog(Type type, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::add_tohop_dialog)
{
    ui->setupUi(this);

    auto monhoc_list = getAllMonHoc();
    for (const auto &monhoc : *monhoc_list){
        ui->mon_1->addItem(monhoc->ten_monhoc, QVariant::fromValue(monhoc->id_monhoc));
        ui->mon_2->addItem(monhoc->ten_monhoc, QVariant::fromValue(monhoc->id_monhoc));
        ui->mon_3->addItem(monhoc->ten_monhoc, QVariant::fromValue(monhoc->id_monhoc));
    }
    this->type = type;

    switch (this->type) {
        case Type::ADD:
            ui->accept->setText("Thêm");
            break;
        case Type::CHANGE:
            ui->accept->setText("Thay đổi");
            break;
    }
}

add_tohop_dialog::~add_tohop_dialog(){
    delete ui;
}

void add_tohop_dialog::setToHop(tohop_mon_ptr &tohop){
    this->tohop = tohop;
    ui->ma_tohop->setText(tohop->ma_tohop);
    int index = ui->mon_1->findData(QVariant::fromValue(tohop->mon_1->id_monhoc));
    ui->mon_1->setCurrentIndex(index);

    index = ui->mon_2->findData(QVariant::fromValue(tohop->mon_2->id_monhoc));
    ui->mon_2->setCurrentIndex(index);

    index = ui->mon_3->findData(QVariant::fromValue(tohop->mon_3->id_monhoc));
    ui->mon_3->setCurrentIndex(index);
}

void add_tohop_dialog::on_accept_clicked(){
    QString ma_tohop = ui->ma_tohop->text();
    long id_mon_1 = ui->mon_1->currentData().toLongLong();
    long id_mon_2 = ui->mon_2->currentData().toLongLong();
    long id_mon_3 = ui->mon_3->currentData().toLongLong();
    switch (this->type) {
        case Type::ADD:{
            if (!addToHop(ma_tohop, id_mon_1, id_mon_2, id_mon_3)) custom_message_box("", "Thêm thất bại", custom_message_box::Error).exec();
            else accept();
        }
            break;
        case Type::CHANGE:{
            if (!tohop) {
                custom_message_box("", "Môn học null", custom_message_box::Error).exec();
                return;
            }
            tohop->ma_tohop = ma_tohop;
            tohop->mon_1 = std::make_shared<mon_hoc>(id_mon_1);
            tohop->mon_2 = std::make_shared<mon_hoc>(id_mon_2);
            tohop->mon_3 = std::make_shared<mon_hoc>(id_mon_3);
            QSqlError err = qx::dao::update(tohop);

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

