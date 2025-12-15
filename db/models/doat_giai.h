#ifndef DOAT_GIAI_H
#define DOAT_GIAI_H

#include <QString>
#include <QxOrm.h>
#include "db/models/thi_sinh.h"
#include "db/models/mon_hoc.h"
#include "db/models/ptxt.h"
#include "db/models/ma_thanhtich.h"

class doat_giai
{
public:
    long id;
    thi_sinh_ptr thi_sinh;
    mon_hoc_ptr mon_hoc;
    ma_thanhtich_ptr thanh_tich;
    int diem_thanh_tich;
    ptxt_ptr ptxt;

    doat_giai();
    doat_giai(long &id) : id(id){};
};

typedef std::shared_ptr<doat_giai> doat_giai_ptr;

QX_REGISTER_HPP(doat_giai, qx::trait::no_base_class_defined, 0)

#endif // DOAT_GIAI_H
