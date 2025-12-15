#ifndef KVUT_DIALOG_H
#define KVUT_DIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "db/models/ma_kvut.h"

namespace Ui {
class kvut_dialog;
}

class kvut_dialog : public QDialog
{
    Q_OBJECT

public:
    enum Type{
        ADD,
        CHANGE
    };
    uint8_t type;

    explicit kvut_dialog(Type type = Type::ADD, QWidget *parent = nullptr);
    ~kvut_dialog();

    ma_kvut_ptr edit_item;
    void setEditItem(ma_kvut_ptr &item);

private:
    Ui::kvut_dialog *ui;
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

#endif // KVUT_DIALOG_H
