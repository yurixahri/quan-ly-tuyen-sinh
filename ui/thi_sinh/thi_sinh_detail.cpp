#include "thi_sinh_detail.h"
#include "ui_thi_sinh_detail.h"

thi_sinh_detail::thi_sinh_detail(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::thi_sinh_detail)
{
    ui->setupUi(this);
}

thi_sinh_detail::~thi_sinh_detail()
{
    delete ui;
}
