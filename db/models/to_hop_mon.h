#ifndef TO_HOP_MON_H
#define TO_HOP_MON_H

#include <QString>
#include <QxOrm.h>
#include "mon_hoc.h"

class ma_nganh;
class mon_hoc;

class tohop_mon
{
public:
    typedef std::shared_ptr<ma_nganh> ma_nganh_ptr;
    long id_tohop;
    QString ma_tohop;
    mon_hoc_ptr mon_1;
    mon_hoc_ptr mon_2;
    mon_hoc_ptr mon_3;

    tohop_mon();
    tohop_mon(long id){
        this->id_tohop = id;
    }
};

typedef std::shared_ptr<tohop_mon> tohop_mon_ptr;

inline QDataStream &operator<<(QDataStream &out, const tohop_mon &m) {
    out << qint64(m.id_tohop) << m.ma_tohop;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, tohop_mon &m) {
    qint64 id = 0;
    in >> id;
    m.id_tohop = static_cast<long>(id);
    in >> m.ma_tohop;
    return in;
}

Q_DECLARE_METATYPE(tohop_mon)
Q_DECLARE_METATYPE(tohop_mon_ptr)

QX_REGISTER_HPP(tohop_mon, qx::trait::no_base_class_defined, 0)


#endif // TO_HOP_MON_H
