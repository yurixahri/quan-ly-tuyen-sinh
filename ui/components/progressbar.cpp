#include "progressbar.h"
#include "ui_progressbar.h"

progressBar::progressBar(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::progressBar)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
}

progressBar::~progressBar()
{
    delete ui;
}

void progressBar::setInitValue(int value){
    init_value = value;
    ui->progress_bar->setRange(0, init_value);
    ui->progress_bar->setValue(0);
}

void progressBar::setCurrentValue(int value){
    current_value = value;
    ui->progress_bar->setValue(current_value);
}

void progressBar::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && ui->drag_area->geometry().contains(event->pos())) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        m_dragging = true;
    }
}

void progressBar::mouseMoveEvent(QMouseEvent *event){
    if (m_dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPosition().toPoint() - m_dragPosition);
    }
}

void progressBar::mouseReleaseEvent(QMouseEvent *event){
    m_dragging = false;
}

void progressBar::on_close_clicked(){
    is_closed = true;
    reject();
}

