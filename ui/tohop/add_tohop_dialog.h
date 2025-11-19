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

private:
    Ui::add_tohop_dialog *ui;
};

#endif // ADD_TOHOP_DIALOG_H
