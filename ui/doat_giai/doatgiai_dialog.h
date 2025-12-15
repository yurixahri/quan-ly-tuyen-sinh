#ifndef DOATGIAI_DIALOG_H
#define DOATGIAI_DIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "db/models/ma_thanhtich.h"

namespace Ui {
class doatgiai_dialog;
}

class doatgiai_dialog : public QDialog
{
    Q_OBJECT

public:
    enum Type{
        ADD,
        CHANGE
    };
    uint8_t type;

    explicit doatgiai_dialog(Type type = Type::ADD, QWidget *parent = nullptr);
    ~doatgiai_dialog();

    ma_thanhtich_ptr edit_item;
    void setEditItem(ma_thanhtich_ptr &item);

private:
    Ui::doatgiai_dialog *ui;
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

#endif // DOATGIAI_DIALOG_H
