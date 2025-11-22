#include "to_hop_mon.h"
#include "QxPrecompiled.h"
#include <QxOrm_Impl.h>

QX_REGISTER_CPP(to_hop_mon)

namespace qx {
template<>
void register_class(QxClass<to_hop_mon> & t){
    t.setName("tohop_mon");
    t.id(&to_hop_mon::id_tohop, "id_tohop")->setAutoIncrement(true);
    t.data(&to_hop_mon::ma_tohop, "ma_tohop");
    t.relationManyToOne(&to_hop_mon::mon_1, "id_mon_1");
    t.relationManyToOne(&to_hop_mon::mon_2, "id_mon_2");
    t.relationManyToOne(&to_hop_mon::mon_3, "id_mon_3");
}}

to_hop_mon::to_hop_mon() {}
