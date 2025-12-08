#ifndef CHUNGCHI_TIENGANH_DIALOG_H
#define CHUNGCHI_TIENGANH_DIALOG_H

#include <QDialog>

namespace Ui {
class chungchi_tienganh_dialog;
}

class chungchi_tienganh_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit chungchi_tienganh_dialog(QWidget *parent = nullptr);
    ~chungchi_tienganh_dialog();

private:
    Ui::chungchi_tienganh_dialog *ui;
};

#endif // CHUNGCHI_TIENGANH_DIALOG_H
