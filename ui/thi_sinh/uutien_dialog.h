#ifndef UUTIEN_DIALOG_H
#define UUTIEN_DIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "db/models/uutien.h"

namespace Ui {
class uutien_dialog;
}

class uutien_dialog : public QDialog
{
    Q_OBJECT

public:
    enum Type{
        ADD,
        CHANGE
    };
    uint8_t type;

    long id_thi_sinh = -1;

    explicit uutien_dialog(Type type = Type::ADD, QWidget *parent = nullptr);
    ~uutien_dialog();

    uutien_ptr edit_item;
    void setEditItem(uutien_ptr &item);

private:
    Ui::uutien_dialog *ui;
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

#endif // UUTIEN_DIALOG_H
