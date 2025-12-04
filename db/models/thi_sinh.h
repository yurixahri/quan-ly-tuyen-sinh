#ifndef THI_SINH_H
#define THI_SINH_H

#include <QString>
#include <QDate>
#include <QxOrm.h>

class thi_sinh
{
public:
    long id;
    QString cccd;
    QString ho_ten;
    QDate ngay_sinh;
    QString gioi_tinh;
    QString dia_chi;
    QString email;
    QString sdt;
    QString ma_dinh_danh;

    thi_sinh();
    thi_sinh(long &id) : id(id){}
};

typedef std::shared_ptr<thi_sinh> thi_sinh_ptr;

QX_REGISTER_HPP(thi_sinh, qx::trait::no_base_class_defined, 0)

#endif // THI_SINH_H
