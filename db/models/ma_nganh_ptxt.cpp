#include "ma_nganh_ptxt.h"
#include "QxPrecompiled.h"
#include <QxOrm_Impl.h>
#include "ptxt.h"
#include "ma_nganh.h"

QX_REGISTER_CPP(ma_nganh_ptxt)

namespace qx {
template<>
void register_class(QxClass<ma_nganh_ptxt> & t){
    t.setName("ma_nganh_ptxt");
    t.id(&ma_nganh_ptxt::id_nganh, "id_nganh")->setAutoIncrement(false);
    t.relationManyToOne(&ma_nganh_ptxt::ptxt, "id_ptxt");
}}

ma_nganh_ptxt::ma_nganh_ptxt() {}
