#ifndef CCNN_DIALOG_H
#define CCNN_DIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "db/models/ma_chungchinn.h"

namespace Ui {
class ccnn_dialog;
}

class ccnn_dialog : public QDialog
{
    Q_OBJECT

public:
    enum Type{
        ADD,
        CHANGE
    };
    uint8_t type;

    explicit ccnn_dialog(Type type = Type::ADD, QWidget *parent = nullptr);
    ~ccnn_dialog();

    ma_chungchinn_ptr edit_item;
    void setEditItem(ma_chungchinn_ptr &item);

private:
    Ui::ccnn_dialog *ui;
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

#endif // CCNN_DIALOG_H
