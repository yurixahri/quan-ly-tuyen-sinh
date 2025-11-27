#ifndef MA_NGANH_TOHOP_H
#define MA_NGANH_TOHOP_H

#include <QString>
#include <QPair>
#include <QxOrm.h>

class tohop_mon;
class ma_nganh;

class ma_nganh_tohop
{
public:
    // typedef QPair<long, long> type_composite_key;

    // type_composite_key id;
    long id_nganh;
    // long id_tohop;
    std::shared_ptr<ma_nganh> ma_nganh;
    std::shared_ptr<tohop_mon> tohop;

    ma_nganh_tohop();
};


inline QDataStream &operator<<(QDataStream &out, const ma_nganh_tohop &m) {
    out << qint64(m.id_nganh) ;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, ma_nganh_tohop &m) {
    qint64 a, b;
    in >> a >> b;
    m.id_nganh = a;
    return in;
}

// QX_REGISTER_PRIMARY_KEY(ma_nganh_tohop, ma_nganh_tohop::type_composite_key)
QX_REGISTER_HPP(ma_nganh_tohop, qx::trait::no_base_class_defined, 0)

#endif // MA_NGANH_TOHOP_H
