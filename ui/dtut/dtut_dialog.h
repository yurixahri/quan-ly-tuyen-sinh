#ifndef DTUT_DIALOG_H
#define DTUT_DIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "db/models/ma_dtut.h"

namespace Ui {
class dtut_dialog;
}

class dtut_dialog : public QDialog
{
    Q_OBJECT

public:
    enum Type{
        ADD,
        CHANGE
    };
    uint8_t type;

    explicit dtut_dialog(Type type = Type::ADD, QWidget *parent = nullptr);
    ~dtut_dialog();

    ma_dtut_ptr edit_item;
    void setEditItem(ma_dtut_ptr &item);

private:
    Ui::dtut_dialog *ui;
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

#endif // DTUT_DIALOG_H
