#ifndef ADD_TOHOP_DIALOG_H
#define ADD_TOHOP_DIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "db/models/to_hop_mon.h"

namespace Ui {
class add_tohop_dialog;
}

class add_tohop_dialog : public QDialog
{
    Q_OBJECT

public:
    enum Type{
        ADD,
        CHANGE
    };
    explicit add_tohop_dialog(Type type = Type::ADD, QWidget *parent = nullptr);
    ~add_tohop_dialog();
    uint8_t type;

    tohop_mon_ptr tohop;
    void setToHop(tohop_mon_ptr &tohop);
private slots:
    void on_accept_clicked();

    void on_close_clicked();

    void on_cancel_clicked();

private:
    Ui::add_tohop_dialog *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // ADD_TOHOP_DIALOG_H
