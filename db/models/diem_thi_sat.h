#ifndef DIEM_THI_SAT_H
#define DIEM_THI_SAT_H

#include "db/models/thi_sinh.h"

class diem_thi_sat
{
public:
    long id;
    thi_sinh_ptr thi_sinh;
    float reading;
    float writing;
    float math;
    float total;
    diem_thi_sat();
    diem_thi_sat(long &id) : id(id){};
};

typedef std::shared_ptr<diem_thi_sat> diem_thi_sat_ptr;

QX_REGISTER_HPP(diem_thi_sat, qx::trait::no_base_class_defined, 0)

#endif // DIEM_THI_SAT_H
