#ifndef DANG_KY_XET_TUYEN_H
#define DANG_KY_XET_TUYEN_H

#include "db/models/ma_nganh.h"
#include "db/models/thi_sinh.h"
#include "db/models/ptxt.h"

class dang_ky_xet_tuyen
{
public:
    long id_thi_sinh = 0;
    long id_ma_nganh = 0;

    thi_sinh_ptr thi_sinh;
    ma_nganh_ptr ma_nganh;
    ptxt_ptr ptxt;
    float diem;
    QString trang_thai;
    dang_ky_xet_tuyen();
};

typedef std::shared_ptr<dang_ky_xet_tuyen> dang_ky_xet_tuyen_ptr;

QX_REGISTER_HPP(dang_ky_xet_tuyen, qx::trait::no_base_class_defined, 0)

#endif // DANG_KY_XET_TUYEN_H
