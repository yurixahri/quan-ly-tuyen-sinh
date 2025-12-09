#ifndef DOAT_GIAI_DIALOG_H
#define DOAT_GIAI_DIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "db/models/doat_giai.h"

namespace Ui {
class doat_giai_dialog;
}

class doat_giai_dialog : public QDialog
{
    Q_OBJECT

public:
    enum Type{
        ADD,
        CHANGE
    };
    uint8_t type;

    explicit doat_giai_dialog(Type type, QWidget *parent = nullptr);
    ~doat_giai_dialog();

    doat_giai_ptr edit_item;
    long id_thi_sinh;
    void setEditItem(doat_giai_ptr &item);

    void loadPtxt();
    void loadMonHoc();
private:
    Ui::doat_giai_dialog *ui;
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

#endif // DOAT_GIAI_DIALOG_H
