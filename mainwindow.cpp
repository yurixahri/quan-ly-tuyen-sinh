#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "pages/monhoc_page.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_monhoc_button_clicked(){
    fillMonHocTable(ui->mon_hoc_table);
}

