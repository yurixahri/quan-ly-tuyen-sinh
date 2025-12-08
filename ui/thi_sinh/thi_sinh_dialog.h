#ifndef THI_SINH_DIALOG_H
#define THI_SINH_DIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "db/models/thi_sinh.h"

namespace Ui {
class thi_sinh_dialog;
}

class thi_sinh_dialog : public QDialog
{
    Q_OBJECT

public:
    enum Type{
        ADD,
        CHANGE
    };
    uint8_t type;

    explicit thi_sinh_dialog(Type type, QWidget *parent = nullptr);
    ~thi_sinh_dialog();

    thi_sinh_ptr edit_item;
    void setEditItem(thi_sinh_ptr &item);
private:
    Ui::thi_sinh_dialog *ui;
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

#endif // THI_SINH_DIALOG_H
