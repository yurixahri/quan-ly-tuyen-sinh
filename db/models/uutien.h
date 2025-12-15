#ifndef UUTIEN_H
#define UUTIEN_H

#include "db/models/ma_dtut.h"
#include "db/models/ma_kvut.h"
#include "db/models/thi_sinh.h"

class uutien
{
public:
    long id;
    thi_sinh_ptr thi_sinh;
    ma_dtut_ptr dtut;
    ma_kvut_ptr kvut;
    uutien();
    uutien(long &id) : id(id) {};
};

typedef std::shared_ptr<uutien> uutien_ptr;

QX_REGISTER_HPP(uutien, qx::trait::no_base_class_defined, 0)

#endif // UUTIEN_H
