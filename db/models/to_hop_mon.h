#ifndef TO_HOP_MON_H
#define TO_HOP_MON_H

#include <QString>
#include <QxOrm.h>

class mon_hoc;

class to_hop_mon
{
public:
    long id_tohop;
    QString ma_tohop;
    std::shared_ptr<mon_hoc> mon_1;
    std::shared_ptr<mon_hoc> mon_2;
    std::shared_ptr<mon_hoc> mon_3;

    to_hop_mon();
    to_hop_mon(long id){
        this->id_tohop = id;
    }
};

typedef std::shared_ptr<to_hop_mon> tohop_mon_ptr;

QX_REGISTER_HPP(to_hop_mon, qx::trait::no_base_class_defined, 0)


#endif // TO_HOP_MON_H
