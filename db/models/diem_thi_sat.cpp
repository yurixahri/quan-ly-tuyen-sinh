#include "diem_thi_sat.h"

QX_REGISTER_CPP(diem_thi_sat)

namespace qx {
template<> void register_class(QxClass<diem_thi_sat> & t)
{
    t.setName("diem_thi_sat");
    t.id(&diem_thi_sat::id, "id_sat");
    t.data(&diem_thi_sat::reading, "reading");
    t.data(&diem_thi_sat::writing, "writing");
    t.data(&diem_thi_sat::math, "math");
    t.data(&diem_thi_sat::total, "total");
    t.relationManyToOne(&diem_thi_sat::thi_sinh, "id_thi_sinh");
}
}

diem_thi_sat::diem_thi_sat() {}
