#include "uutien.h"

QX_REGISTER_CPP(uutien)

namespace qx {
template<> void register_class(QxClass<uutien> & t)
{
    t.setName("dt_kv_uutien");
    t.id(&uutien::id, "id");
    t.relationManyToOne(&uutien::thi_sinh, "id_thi_sinh");
    t.relationManyToOne(&uutien::dtut, "dt_ut");
    t.relationManyToOne(&uutien::kvut, "kv_ut");
}
}

uutien::uutien() {}
