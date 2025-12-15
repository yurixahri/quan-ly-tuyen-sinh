#ifndef MA_THANHTICH_H
#define MA_THANHTICH_H

#include <QString>
#include <QxOrm.h>

class ma_thanhtich
{
public:
    long id;
    QString ma;
    QString ten = "";
    float diem = 0;
    ma_thanhtich();
    ma_thanhtich(long &id) : id(id) {};
};

typedef std::shared_ptr<ma_thanhtich> ma_thanhtich_ptr;

inline QDataStream &operator<<(QDataStream &out, const ma_thanhtich &m) {
    out << qint64(m.id) ;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, ma_thanhtich &m) {
    qint64 a;
    in >> a;
    m.id = a;
    return in;
}

QX_REGISTER_HPP(ma_thanhtich, qx::trait::no_base_class_defined, 0)

#endif // MA_THANHTICH_H
