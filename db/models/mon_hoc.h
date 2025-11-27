#ifndef MON_HOC_H
#define MON_HOC_H

#include <QString>
#include <QxOrm.h>


class mon_hoc
{
public:
    long id_monhoc{};
    QString ten_monhoc;

    mon_hoc();
    mon_hoc(long id){
        this->id_monhoc = id;
    }
};

typedef std::shared_ptr<mon_hoc> mon_hoc_ptr;

inline QDataStream &operator<<(QDataStream &out, const mon_hoc &m) {
    out << qint64(m.id_monhoc) << m.ten_monhoc;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, mon_hoc &m) {
    qint64 id = 0;
    in >> id;
    m.id_monhoc = static_cast<long>(id);
    in >> m.ten_monhoc;
    return in;
}

Q_DECLARE_METATYPE(mon_hoc)
Q_DECLARE_METATYPE(mon_hoc_ptr)

QX_REGISTER_HPP(mon_hoc, qx::trait::no_base_class_defined, 0)

#endif // MON_HOC_H
