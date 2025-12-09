#ifndef DIEM_HOCBA_DIALOG_H
#define DIEM_HOCBA_DIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "db/models/diem_hocba.h"

namespace Ui {
class diem_hocba_dialog;
}

class diem_hocba_dialog : public QDialog
{
    Q_OBJECT

public:
    enum Type{
        ADD,
        CHANGE
    };
    uint8_t type;

    explicit diem_hocba_dialog(Type type, QWidget *parent = nullptr);
    ~diem_hocba_dialog();

    diem_hocba_ptr edit_item;
    long id_thi_sinh;
    void setEditItem(diem_hocba_ptr &item);

private:
    Ui::diem_hocba_dialog *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void on_close_clicked();
    void on_cancel_clicked();
    void on_accept_clicked();
};

#endif // DIEM_HOCBA_DIALOG_H
