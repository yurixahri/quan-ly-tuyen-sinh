#ifndef NGANH_H
#define NGANH_H

#include <QString>
#include <QxOrm.h>
#include "db/models/nhom_nganh.h"

class nhom_nganh;

class nganh
{
public:
    long id;
    QString ma_nganh;
    QString ten_nganh;
    // QString ma_truong;
    // QString ten_truong;
    nhom_nganh_ptr nhom_nganh;

    nganh();
    nganh(long id){
        this->id = id;
    };
};

typedef std::shared_ptr<nganh> nganh_ptr;

QX_REGISTER_HPP(nganh, qx::trait::no_base_class_defined, 0)

#endif // NGANH_H
