#include "chungchi_tienganh.h"

QX_REGISTER_CPP(chungchi_tienganh)

namespace qx {
template<> void register_class(QxClass<chungchi_tienganh> & t)
{
    t.setName("chungchi_tienganh");
    t.id(&chungchi_tienganh::id, "id_cc");
    t.data(&chungchi_tienganh::loai_chungchi, "loai_chungchi");
    t.data(&chungchi_tienganh::diem, "diem");
    t.data(&chungchi_tienganh::ngay_cap, "ngay_cap");
    t.data(&chungchi_tienganh::ngay_het_han, "ngay_het_han");
    t.relationManyToOne(&chungchi_tienganh::thi_sinh, "id_thi_sinh");
}
}

chungchi_tienganh::chungchi_tienganh() {}
