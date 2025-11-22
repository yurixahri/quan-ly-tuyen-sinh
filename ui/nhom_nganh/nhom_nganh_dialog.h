#ifndef NHOM_NGANH_DIALOG_H
#define NHOM_NGANH_DIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "db/models/nhom_nganh.h"

namespace Ui {
class nhom_nganh_dialog;
}

class nhom_nganh_dialog : public QDialog
{
    Q_OBJECT

public:
    enum Type{
        ADD,
        CHANGE
    };
    uint8_t type;

    explicit nhom_nganh_dialog(Type type = Type::ADD, QWidget *parent = nullptr);
    ~nhom_nganh_dialog ();

    nhom_nganh_ptr edit_item;
    void setEditItem(nhom_nganh_ptr &item);
private:
    Ui::nhom_nganh_dialog *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private slots:
    void on_accept_clicked();
    void on_cancel_clicked();
    void on_close_clicked();
};

#endif // NHOM_NGANH_DIALOG_H
