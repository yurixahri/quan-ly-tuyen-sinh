#ifndef MA_KVUT_H
#define MA_KVUT_H

#include <QString>
#include <QxOrm.h>

class ma_kvut
{
public:
    long id;
    QString ma;
    QString ten = "";
    float diem = 0;
    ma_kvut();
    ma_kvut(long &id) :id(id){};
};

typedef std::shared_ptr<ma_kvut> ma_kvut_ptr;

inline QDataStream &operator<<(QDataStream &out, const ma_kvut &m) {
    out << qint64(m.id) << m.ma<< m.ten;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, ma_kvut &m) {
    qint64 id = 0;
    in >> id >> m.ma >> m.ten;
    m.id = static_cast<long>(id);
    return in;
}

Q_DECLARE_METATYPE(ma_kvut)
Q_DECLARE_METATYPE(ma_kvut_ptr)

QX_REGISTER_HPP(ma_kvut, qx::trait::no_base_class_defined, 0)
#endif // MA_KVUT_H
