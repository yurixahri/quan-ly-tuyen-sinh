#include "dang_ky_xet_tuyen.h"

QX_REGISTER_CPP(dang_ky_xet_tuyen)

namespace qx {
template<> void register_class(QxClass<dang_ky_xet_tuyen> & t)
{
    t.setName("dang_ky_xet_tuyen");
    t.id(&dang_ky_xet_tuyen::id_thi_sinh, "id_thi_sinh")->setAutoIncrement(false);
    t.id(&dang_ky_xet_tuyen::id_ma_nganh, "id_ma_nganh")->setAutoIncrement(false);

    t.relationManyToOne(&dang_ky_xet_tuyen::thi_sinh, "id_thi_sinh");
    t.relationManyToOne(&dang_ky_xet_tuyen::ma_nganh, "id_ma_nganh");
    t.relationManyToOne(&dang_ky_xet_tuyen::ptxt, "id_ptxt");
    t.data(&dang_ky_xet_tuyen::diem, "diem_xt");
    t.data(&dang_ky_xet_tuyen::trang_thai, "trang_thai");
}
}

dang_ky_xet_tuyen::dang_ky_xet_tuyen() {}
