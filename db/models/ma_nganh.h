#ifndef MA_NGANH_H
#define MA_NGANH_H

#include <QString>
#include <QxOrm.h>
#include "db/models/nganh.h"
#include "db/models/ma_nganh_tohop.h"
#include "db/models/ma_nganh_ptxt.h"

class ma_nganh
{
public:
    long id;
    int chi_tieu;
    QString ghi_chu;

    nganh_ptr nganh;
    QList<std::shared_ptr<ma_nganh_tohop>> list_tohop;
    QList<std::shared_ptr<ma_nganh_ptxt>> list_ptxt;
    ma_nganh();
    ma_nganh(long id){
        this->id = id;
    }
};

typedef std::shared_ptr<ma_nganh> ma_nganh_ptr;

inline QDataStream &operator<<(QDataStream &out, const ma_nganh &m) {
    out << qint64(m.id) << m.chi_tieu << m.ghi_chu;
    return out;
}

inline QDataStream &operator>>(QDataStream &in, ma_nganh &m) {
    qint64 id = 0;
    in >> id >> m.chi_tieu >> m .ghi_chu;
    m.id = static_cast<long>(id);
    return in;
}

Q_DECLARE_METATYPE(ma_nganh)
Q_DECLARE_METATYPE(ma_nganh_ptr)

QX_REGISTER_HPP(ma_nganh, qx::trait::no_base_class_defined, 0)

#endif // MA_NGANH_H
