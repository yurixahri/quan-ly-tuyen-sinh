#ifndef MA_NGANH_DIALOG_H
#define MA_NGANH_DIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "db/models/ma_nganh.h"

namespace Ui {
class ma_nganh_dialog;
}

class ma_nganh_dialog : public QDialog
{
    Q_OBJECT

public:
    enum Type{
        ADD,
        CHANGE
    };
    uint8_t type;

    explicit ma_nganh_dialog(Type type = Type::ADD, QWidget *parent = nullptr);
    ~ma_nganh_dialog();

    ma_nganh_ptr edit_item;
    void setEditItem(ma_nganh_ptr &item);
private:
    Ui::ma_nganh_dialog *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;
    void update();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private slots:
    void on_accept_clicked();
    void on_cancel_clicked();
    void on_close_clicked();
};

#endif // MA_NGANH_DIALOG_H
