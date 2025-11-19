#include "custom_message_box.h"
#include "ui_custom_message_box.h"

custom_message_box::custom_message_box(const QString &title,
                                       const QString &message,
                                       MessageType type,
                                       bool askConfirm,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::custom_message_box)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    ui->message->setText(message);

    QIcon icon;
    switch (type) {
    case Information:
        icon.addFile(":/assets/images/info-96.png");
        break;
    case Warning:
        QApplication::beep();
        icon.addFile(":/assets/images/warning-96.png");
        break;
    case Error:
        QApplication::beep();
        icon.addFile(":/assets/images/error-96.png");
        break;
    case Question:
        icon.addFile(":/assets/images/question-96.png");
        break;
    }

    ui->icon->setPixmap(icon.pixmap(96, 96));
    if (askConfirm) {
        ui->cancel->show();
        connect(ui->cancel, &QPushButton::clicked, this, &QDialog::reject);
    } else {
        ui->cancel->hide();
    }

    connect(ui->accept, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->close, &QPushButton::clicked, this, &QDialog::reject);
}

custom_message_box::~custom_message_box()
{
    delete ui;
}

void custom_message_box::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void custom_message_box::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void custom_message_box::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}
