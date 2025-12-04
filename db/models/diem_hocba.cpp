#include "diem_hocba.h"

QX_REGISTER_CPP(diem_hocba)

namespace qx {
template<> void register_class(QxClass<diem_hocba> & t)
{
    t.setName("diem_hocba");
    t.id(&diem_hocba::id, "id_diem");
    t.data(&diem_hocba::lop10, "lop10");
    t.data(&diem_hocba::lop11, "lop11");
    t.data(&diem_hocba::lop12, "lop12");
    t.relationManyToOne(&diem_hocba::mon_hoc, "id_monhoc");
    t.relationManyToOne(&diem_hocba::thi_sinh, "id_thi_sinh");
}
}

diem_hocba::diem_hocba() {}
