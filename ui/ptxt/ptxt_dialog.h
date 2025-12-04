#ifndef PTXT_DIALOG_H
#define PTXT_DIALOG_H

#include <QMouseEvent>
#include <QDialog>
#include "db/models/ptxt.h"

namespace Ui {
class ptxt_dialog;
}

class ptxt_dialog : public QDialog
{
    Q_OBJECT

public:
    enum Type{
        ADD,
        CHANGE
    };
    uint8_t type;

    explicit ptxt_dialog(Type type = Type::ADD, QWidget *parent = nullptr);
    ~ptxt_dialog();

    ptxt_ptr edit_item;
    void setEditItem(ptxt_ptr &item);
private:
    Ui::ptxt_dialog *ui;
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

#endif // PTXT_DIALOG_H
