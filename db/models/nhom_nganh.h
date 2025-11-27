#ifndef NHOM_NGANH_H
#define NHOM_NGANH_H

#include <QString>
#include <QxOrm.h>

class nhom_nganh
{
public:
    long id_nhom_nganh;
    QString ten;

    nhom_nganh();
    nhom_nganh(long id){
        this->id_nhom_nganh = id;
        this->ten = "";
    };
};

typedef std::shared_ptr<nhom_nganh> nhom_nganh_ptr;

inline QDataStream &operator<<(QDataStream &out, const nhom_nganh &m) {
    out << qint64(m.id_nhom_nganh) << m.ten;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, nhom_nganh &m) {
    qint64 id = 0;
    in >> id;
    m.id_nhom_nganh = static_cast<long>(id);
    in >> m.ten;
    return in;
}

Q_DECLARE_METATYPE(nhom_nganh)
Q_DECLARE_METATYPE(nhom_nganh_ptr)

QX_REGISTER_HPP(nhom_nganh, qx::trait::no_base_class_defined, 0)

#endif // NHOM_NGANH_H
