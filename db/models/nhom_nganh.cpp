#include "nhom_nganh.h"
#include "QxPrecompiled.h"
#include <QxOrm_Impl.h>

QX_REGISTER_CPP(nhom_nganh)

namespace qx {
template<>
void register_class(QxClass<nhom_nganh> & t){
    t.setName("nhom_nganh");
    t.id(&nhom_nganh::id_nhom_nganh, "id_nhom_nganh")->setAutoIncrement(true);
    t.data(&nhom_nganh::ten, "ten_nhom_nganh");
}}

nhom_nganh::nhom_nganh() {}
