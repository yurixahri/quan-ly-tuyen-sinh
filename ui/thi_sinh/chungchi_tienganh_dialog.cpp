#include "chungchi_tienganh_dialog.h"
#include "ui_chungchi_tienganh_dialog.h"

chungchi_tienganh_dialog::chungchi_tienganh_dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::chungchi_tienganh_dialog)
{
    ui->setupUi(this);
}

chungchi_tienganh_dialog::~chungchi_tienganh_dialog()
{
    delete ui;
}
