#include "chungchi_tienganh.h"

QX_REGISTER_CPP(chungchi_tienganh)

namespace qx {
template<> void register_class(QxClass<chungchi_tienganh> & t)
{
    t.setName("chungchi_tienganh");
    t.id(&chungchi_tienganh::id, "id_cc");
    t.data(&chungchi_tienganh::diem, "diem");
    t.relationManyToOne(&chungchi_tienganh::thi_sinh, "id_thi_sinh");
    t.relationManyToOne(&chungchi_tienganh::ccnn, "id_ccnn");
    t.relationManyToOne(&chungchi_tienganh::ptxt, "id_ptxt");
}
}

chungchi_tienganh::chungchi_tienganh() {}
