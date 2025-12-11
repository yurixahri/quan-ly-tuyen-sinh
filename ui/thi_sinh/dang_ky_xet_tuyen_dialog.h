#ifndef DANG_KY_XET_TUYEN_DIALOG_H
#define DANG_KY_XET_TUYEN_DIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "db/models/dang_ky_xet_tuyen.h"

namespace Ui {
class dang_ky_xet_tuyen_dialog;
}

class dang_ky_xet_tuyen_dialog : public QDialog
{
    Q_OBJECT

public:
    enum Type {
        ADD,
        CHANGE
    };
    uint8_t type;

    explicit dang_ky_xet_tuyen_dialog(Type type, QWidget *parent = nullptr);
    ~dang_ky_xet_tuyen_dialog();

    dang_ky_xet_tuyen_ptr edit_item;
    long id_thi_sinh = 0;
    void setEditItem(dang_ky_xet_tuyen_ptr &item);

private:
    Ui::dang_ky_xet_tuyen_dialog *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;

    void loadMaNganh();
    void loadPtxt();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void on_close_clicked();
    void on_cancel_clicked();
    void on_accept_clicked();
};

#endif // DANG_KY_XET_TUYEN_DIALOG_H
