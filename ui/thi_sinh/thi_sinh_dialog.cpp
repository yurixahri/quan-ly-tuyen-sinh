#include "thi_sinh_dialog.h"
#include "ui_thi_sinh_dialog.h"

thi_sinh_dialog::thi_sinh_dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::thi_sinh_dialog)
{
    ui->setupUi(this);
}

thi_sinh_dialog::~thi_sinh_dialog()
{
    delete ui;
}
