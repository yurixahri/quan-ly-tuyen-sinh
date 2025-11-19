#ifndef ADD_MON_HOC_DIALOG_H
#define ADD_MON_HOC_DIALOG_H

#include <QDialog>
#include <QMouseEvent>

namespace Ui {
class add_mon_hoc_dialog;
}

class add_mon_hoc_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit add_mon_hoc_dialog(QWidget *parent = nullptr);
    ~add_mon_hoc_dialog();

private slots:
    void on_accept_clicked();

    void on_cancel_clicked();

    void on_close_clicked();

private:
    Ui::add_mon_hoc_dialog *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // ADD_MON_HOC_DIALOG_H
