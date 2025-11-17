#include "logindialog.h"
#include "ui_logindialog.h"
#include "excel/read_excel.h"

loginDialog::loginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::loginDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    //ui->verticalSpacer->changeSize(0,0, QSizePolicy::Expanding, QSizePolicy::Expanding);
    //ui->verticalSpacer->setGeometry(0,0)
    //setFixedSize(800, 400);
    //db = QSqlDatabase::addDatabase("QPSQL");
    qDebug() << readExcel("F:/Đồ Án Tốt Nghiệp 2025/File-du-lieu-tuyen-sinnh-2025 (3).xlsx");
}

loginDialog::~loginDialog(){
    delete ui;
}

void loginDialog::on_login_button_clicked(){
    host_name = ui->host_name->text();
    database_name = ui->database_name->text();
    database_port = ui->database_port->text().toUShort();
    username = ui->username->text();
    password = ui->password->text();

    if(!beginQX_DB(qx_db))
        QMessageBox::warning(this, " ", "Login Failed");
    else
        QMessageBox::information(this, " ", "Successful Login");
    accept();
}


void loginDialog::on_close_clicked(){
    reject();
}

void loginDialog::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void loginDialog::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void loginDialog::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}

