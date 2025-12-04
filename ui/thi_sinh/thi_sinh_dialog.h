#ifndef THI_SINH_DIALOG_H
#define THI_SINH_DIALOG_H

#include <QDialog>

namespace Ui {
class thi_sinh_dialog;
}

class thi_sinh_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit thi_sinh_dialog(QWidget *parent = nullptr);
    ~thi_sinh_dialog();

private:
    Ui::thi_sinh_dialog *ui;
};

#endif // THI_SINH_DIALOG_H
