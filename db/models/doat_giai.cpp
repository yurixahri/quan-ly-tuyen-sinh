#include "doat_giai.h"

QX_REGISTER_CPP(doat_giai)

namespace qx {
template<> void register_class(QxClass<doat_giai> & t)
{
    t.setName("doat_giai");
    t.id(&doat_giai::id, "id_giai")->setAutoIncrement(true);
    t.data(&doat_giai::diem_thanh_tich, "diem_thanh_tich");
    t.relationManyToOne(&doat_giai::thanh_tich, "thanh_tich");
    t.relationManyToOne(&doat_giai::thi_sinh, "id_thi_sinh");
    t.relationManyToOne(&doat_giai::mon_hoc, "id_monhoc");
    t.relationManyToOne(&doat_giai::ptxt, "id_ptxt");
}
}

doat_giai::doat_giai() {}
