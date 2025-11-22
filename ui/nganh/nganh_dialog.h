#ifndef NGANH_DIALOG_H
#define NGANH_DIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "db/nganh_dao.h"

namespace Ui {
class nganh_dialog;
}

class nganh_dialog : public QDialog
{
    Q_OBJECT

public:
    enum Type{
        ADD,
        CHANGE
    };
    uint8_t type;

    explicit nganh_dialog(Type type = Type::ADD,QWidget *parent = nullptr);
    ~nganh_dialog();

    nganh_ptr edit_item;
    void setEditItem(nganh_ptr &item);
private:
    Ui::nganh_dialog *ui;
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

#endif // NGANH_DIALOG_H
