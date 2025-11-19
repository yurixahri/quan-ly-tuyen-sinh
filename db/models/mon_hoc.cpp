#include "mon_hoc.h"
#include "QxPrecompiled.h"
#include <QxOrm_Impl.h>

QX_REGISTER_CPP(mon_hoc)

namespace qx {
template<>
void register_class(QxClass<mon_hoc> & t){
    t.setName("mon_hoc");
    t.id(&mon_hoc::id_monhoc, "id_monhoc")->setAutoIncrement(true);
    t.data(&mon_hoc::ten_monhoc, "ten_monhoc");
}}

mon_hoc::mon_hoc(){
}
