#ifndef CHUNGCHI_TIENGANH_H
#define CHUNGCHI_TIENGANH_H

#include "db/models/thi_sinh.h"
#include "db/models/ma_chungchinn.h"
#include "db/models/ptxt.h"
#include <QxOrm.h>

class chungchi_tienganh
{
public:
    long id;
    thi_sinh_ptr thi_sinh;
    float diem;
    ma_chungchinn_ptr ccnn;
    ptxt_ptr ptxt;

    chungchi_tienganh();
    chungchi_tienganh(long &id) : id(id){};
};

typedef std::shared_ptr<chungchi_tienganh> chungchi_tienganh_ptr;

QX_REGISTER_HPP(chungchi_tienganh, qx::trait::no_base_class_defined, 0)

#endif // CHUNGCHI_TIENGANH_H
