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
    long id_nhom_nganh;
    nhom_nganh_ptr nhom_nganh;

    nganh() : id(0), id_nhom_nganh(0) {};
    nganh(long id){
        this->id = id;
        this->id_nhom_nganh = 0;
    };
};

typedef std::shared_ptr<nganh> nganh_ptr;

inline QDataStream &operator<<(QDataStream &out, const nganh &m) {
    out << qint64(m.id) << m.ma_nganh << m.ten_nganh << m.nhom_nganh->ten;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, nganh &m) {
    qint64 id = 0;
    in >> id;
    m.id = static_cast<long>(id);
    in >> m.ma_nganh;
    in >> m.ten_nganh;
    return in;
}

Q_DECLARE_METATYPE(nganh)
Q_DECLARE_METATYPE(nganh_ptr)

QX_REGISTER_HPP(nganh, qx::trait::no_base_class_defined, 0)

#endif // NGANH_H
