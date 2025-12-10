#ifndef DIEM_HOCBA_H
#define DIEM_HOCBA_H

#include "db/models/thi_sinh.h"
#include "db/models/mon_hoc.h"

class diem_hocba
{
public:
    long id;
    thi_sinh_ptr thi_sinh;
    mon_hoc_ptr mon_hoc;
    float lop10 = 0;
    float lop11 = 0;
    float lop12 = 0;
    diem_hocba();
    diem_hocba(long &id) : id(id){};
};

typedef std::shared_ptr<diem_hocba> diem_hocba_ptr;

QX_REGISTER_HPP(diem_hocba, qx::trait::no_base_class_defined, 0)

#endif // DIEM_HOCBA_H
