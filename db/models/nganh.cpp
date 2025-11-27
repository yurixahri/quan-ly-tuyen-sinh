#include "db/models/nganh.h"
#include "QxPrecompiled.h"
#include <QxOrm_Impl.h>

QX_REGISTER_CPP(nganh)

namespace qx {
template<>
void register_class(QxClass<nganh> & t){
    t.setName("nganh");
    t.id(&nganh::id, "id_nganh")->setAutoIncrement(true);
    t.data(&nganh::ma_nganh, "ma_nganh");
    t.data(&nganh::ten_nganh, "ten_nganh");
    // t.data(&nganh::id_nhom_nganh, "id_nhom_nganh");
    t.relationManyToOne(&nganh::nhom_nganh, "id_nhom_nganh");
}}
