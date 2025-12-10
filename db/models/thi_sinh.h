#ifndef THI_SINH_H
#define THI_SINH_H

#include <QString>
#include <QDate>
#include <QxOrm.h>

class thi_sinh
{
public:
    long id;
    QString cccd = "";
    QString ho_ten = "";
    QDate ngay_sinh;
    QString gioi_tinh = "";
    QString dia_chi = "";
    QString email = "";
    QString sdt = "";
    QString sbd = "";

    thi_sinh();
    thi_sinh(long &id) : id(id){}
};

typedef std::shared_ptr<thi_sinh> thi_sinh_ptr;

inline QDataStream &operator<<(QDataStream &out, const thi_sinh &m) {
    out << qint64(m.id) << m.cccd << m.ho_ten << m.ngay_sinh << m.gioi_tinh << m.dia_chi << m.email << m.sdt << m.sbd;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, thi_sinh &m) {
    qint64 id = 0;
    in >> id;
    m.id = static_cast<long>(id);
    return in;
}

QX_REGISTER_HPP(thi_sinh, qx::trait::no_base_class_defined, 0)

#endif // THI_SINH_H
