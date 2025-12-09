#ifndef DIEM_SAT_DIALOG_H
#define DIEM_SAT_DIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "db/models/diem_thi_sat.h"

namespace Ui {
class diem_sat_dialog;
}

class diem_sat_dialog : public QDialog
{
    Q_OBJECT

public:
    enum Type{
        ADD,
        CHANGE
    };
    uint8_t type;

    explicit diem_sat_dialog(Type type, QWidget *parent = nullptr);
    ~diem_sat_dialog();

    diem_thi_sat_ptr edit_item;
    long id_thi_sinh;
    void setEditItem(diem_thi_sat_ptr &item);

private:
    Ui::diem_sat_dialog *ui;
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

#endif // DIEM_SAT_DIALOG_H
