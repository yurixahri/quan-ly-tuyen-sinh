#include "logindialog.h"
#include "ui_logindialog.h"

loginDialog::loginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    setFixedSize(width(), height());
}

loginDialog::~loginDialog()
{
    delete ui;
}
