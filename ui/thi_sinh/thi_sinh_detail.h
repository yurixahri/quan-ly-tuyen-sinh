#ifndef THI_SINH_DETAIL_H
#define THI_SINH_DETAIL_H

#include <QDialog>
#include "db/models/thi_sinh.h"

namespace Ui {
class thi_sinh_detail;
}

class thi_sinh_detail : public QDialog
{
    Q_OBJECT

public:
    explicit thi_sinh_detail(QWidget *parent = nullptr);
    ~thi_sinh_detail();

    thi_sinh_ptr item;
private:
    Ui::thi_sinh_detail *ui;
};

#endif // THI_SINH_DETAIL_H
