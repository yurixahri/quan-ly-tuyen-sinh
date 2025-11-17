#ifndef MON_HOC_H
#define MON_HOC_H

#include <QString>
#include <QxOrm.h>

class tohop_mon;

class mon_hoc
{
public:
    long id_monhoc{};
    QString ma_monhoc;
    QString ten_monhoc;

    mon_hoc();
};

QX_REGISTER_HPP(mon_hoc, qx::trait::no_base_class_defined, 0)

#endif // MON_HOC_H
