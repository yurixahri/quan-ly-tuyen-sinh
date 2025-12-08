#ifndef CHUNGCHI_TIENGANH_H
#define CHUNGCHI_TIENGANH_H

#include "db/models/thi_sinh.h"
#include <QxOrm.h>

class chungchi_tienganh
{
public:
    long id;
    thi_sinh_ptr thi_sinh;
    QString loai_chungchi;
    float diem;
    QDate ngay_cap;
    QDate ngay_het_han;

    chungchi_tienganh();
    chungchi_tienganh(long &id) : id(id){};
};

typedef std::shared_ptr<chungchi_tienganh> chungchi_tienganh_ptr;

QX_REGISTER_HPP(chungchi_tienganh, qx::trait::no_base_class_defined, 0)

#endif // CHUNGCHI_TIENGANH_H
