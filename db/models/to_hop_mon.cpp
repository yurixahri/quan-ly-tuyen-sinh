#include "to_hop_mon.h"
#include "db/models/ma_nganh.h"
#include "QxPrecompiled.h"
#include <QxOrm_Impl.h>
#include "ma_nganh_tohop.h"

QX_REGISTER_CPP(tohop_mon)

namespace qx {
template<>
void register_class(QxClass<tohop_mon> & t){
    t.setName("tohop_mon");
    t.id(&tohop_mon::id_tohop, "id_tohop")->setAutoIncrement(true);
    t.data(&tohop_mon::ma_tohop, "ma_tohop");
    t.relationManyToOne(&tohop_mon::mon_1, "id_mon_1");
    t.relationManyToOne(&tohop_mon::mon_2, "id_mon_2");
    t.relationManyToOne(&tohop_mon::mon_3, "id_mon_3");


}}

tohop_mon::tohop_mon() {}
