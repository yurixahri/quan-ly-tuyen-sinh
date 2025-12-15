#ifndef MA_DTUT_H
#define MA_DTUT_H

#include <QString>
#include <QxOrm.h>

class ma_dtut
{
public:
    long id;
    QString ma;
    QString ten = "";
    float diem = 0;
    ma_dtut();
    ma_dtut(long &id) :id(id){};
};

typedef std::shared_ptr<ma_dtut> ma_dtut_ptr;

inline QDataStream &operator<<(QDataStream &out, const ma_dtut &m) {
    out << qint64(m.id) << m.ma<< m.ten;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, ma_dtut &m) {
    qint64 id = 0;
    in >> id >> m.ma >> m.ten;
    m.id = static_cast<long>(id);
    return in;
}

Q_DECLARE_METATYPE(ma_dtut)
Q_DECLARE_METATYPE(ma_dtut_ptr)

QX_REGISTER_HPP(ma_dtut, qx::trait::no_base_class_defined, 0)

#endif // MA_DTUT_H
