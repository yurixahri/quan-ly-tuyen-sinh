#ifndef CHANGE_MON_HOC_DIALOG_H
#define CHANGE_MON_HOC_DIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "db/monhoc_dao.h"

namespace Ui {
class change_mon_hoc_dialog;
}

class change_mon_hoc_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit change_mon_hoc_dialog(QWidget *parent = nullptr);
    ~change_mon_hoc_dialog();

    mon_hoc_ptr mon_hoc;
    void setMonHoc(mon_hoc_ptr &mon_hoc);

private slots:
    void on_cancel_clicked();

    void on_close_clicked();

    void on_accept_clicked();

private:
    Ui::change_mon_hoc_dialog *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


};

#endif // CHANGE_MON_HOC_DIALOG_H
