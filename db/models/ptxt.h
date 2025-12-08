#ifndef PTXT_H
#define PTXT_H

#include <QString>
#include <QxOrm.h>

class ptxt
{
public:
    long id;
    QString ma;
    QString ten;
    QString mo_ta;
    float thang_diem;

    ptxt();
    ptxt(long id){
        this->id = id;
    }
};

typedef std::shared_ptr<ptxt> ptxt_ptr;

inline QDataStream &operator<<(QDataStream &out, const ptxt &m) {
    out << qint64(m.id) << m.ma << m.ten << m.mo_ta;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, ptxt &m) {
    qint64 id = 0;
    in >> id;
    m.id = static_cast<long>(id);
    in >> m.ma;
    in >> m.ten;
    in >> m.mo_ta;
    return in;
}

Q_DECLARE_METATYPE(ptxt)
Q_DECLARE_METATYPE(ptxt_ptr)

QX_REGISTER_HPP(ptxt, qx::trait::no_base_class_defined, 0)

#endif // PTXT_H
