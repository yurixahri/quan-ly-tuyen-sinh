#ifndef MA_CHUNGCHINN_H
#define MA_CHUNGCHINN_H

#include <QxOrm.h>

class ma_chungchinn
{
public:
    long id;
    QString ma;
    QString ten = "";

    ma_chungchinn();
    ma_chungchinn(long &id) : id(id){};
};

typedef std::shared_ptr<ma_chungchinn> ma_chungchinn_ptr;

inline QDataStream &operator<<(QDataStream &out, const ma_chungchinn &m) {
    out << qint64(m.id) << m.ma<< m.ten;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, ma_chungchinn &m) {
    qint64 id = 0;
    in >> id >> m.ma >> m.ten;
    m.id = static_cast<long>(id);
    return in;
}

Q_DECLARE_METATYPE(ma_chungchinn)
Q_DECLARE_METATYPE(ma_chungchinn_ptr)

QX_REGISTER_HPP(ma_chungchinn, qx::trait::no_base_class_defined, 0)

#endif // MA_CHUNGCHINN_H
