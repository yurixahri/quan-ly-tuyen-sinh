#include "ma_nganh.h"

QX_REGISTER_CPP(ma_nganh)

namespace qx {
template<> void register_class(QxClass<ma_nganh> & t)
{
    t.setName("ma_nganh");
    t.id(&ma_nganh::id, "id")->setAutoIncrement(true);
    t.data(&ma_nganh::chi_tieu, "chi_tieu");
    t.data(&ma_nganh::ghi_chu, "ghi_chu");

    /*t.relationOneToMany(&ma_nganh::list_tohop,
                         "list_tohop",
                         "id_nganh");*/              // column referencing tohop
    // t.relationManyToMany(&ma_nganh::list_ptxt,
    //                      "list_ptxt",
    //                      "ma_nganh_ptxt",
    //                      "id_nganh",
    //                      "id_phuongthuc");
    t.relationManyToOne(&ma_nganh::nganh, "id_nganh");
}
}

ma_nganh::ma_nganh() {}
