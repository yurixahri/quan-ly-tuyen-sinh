#include "ma_nganh_tohop.h"
#include "QxPrecompiled.h"
#include <QxOrm_Impl.h>
#include "to_hop_mon.h"
#include "ma_nganh.h"

QX_REGISTER_CPP(ma_nganh_tohop)

namespace qx {
template<>
void register_class(QxClass<ma_nganh_tohop> & t){
    t.setName("ma_nganh_tohop");
    // t.id(&ma_nganh_tohop::id, "id_nganh|id_tohop")->setAutoIncrement(false);
    t.id(&ma_nganh_tohop::id_nganh, "id_nganh")->setAutoIncrement(false);
    // t.data(&ma_nganh_tohop::tohop, "id_tohop");
    //t.relationManyToOne(&ma_nganh_tohop::ma_nganh, "id_nganh");
    t.relationManyToOne(&ma_nganh_tohop::tohop, "id_tohop");
}}


ma_nganh_tohop::ma_nganh_tohop() {}
