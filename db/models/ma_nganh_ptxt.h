#ifndef MA_NGANH_PTXT_H
#define MA_NGANH_PTXT_H

#include <QString>
#include <QxOrm.h>

class ma_nganh;
class ptxt;

class ma_nganh_ptxt
{
public:
    long id_nganh;
    std::shared_ptr<ma_nganh> ma_nganh;
    std::shared_ptr<ptxt> ptxt;
    ma_nganh_ptxt();
};

inline QDataStream &operator<<(QDataStream &out, const ma_nganh_ptxt &m) {
    out << qint64(m.id_nganh) ;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, ma_nganh_ptxt &m) {
    qint64 a, b;
    in >> a >> b;
    m.id_nganh = a;
    return in;
}

QX_REGISTER_HPP(ma_nganh_ptxt, qx::trait::no_base_class_defined, 0)

#endif // MA_NGANH_PTXT_H
