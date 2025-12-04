#include "thi_sinh.h"

QX_REGISTER_CPP(thi_sinh)

namespace qx {
template<> void register_class(QxClass<thi_sinh> & t)
{
    t.setName("thi_sinh");
    t.id(&thi_sinh::id, "id_thi_sinh");
    t.data(&thi_sinh::cccd, "so_cccd");
    t.data(&thi_sinh::ho_ten, "ho_ten");
    t.data(&thi_sinh::ngay_sinh, "ngay_sinh");
    t.data(&thi_sinh::gioi_tinh, "gioi_tinh");
    t.data(&thi_sinh::dia_chi, "dia_chi");
    t.data(&thi_sinh::email, "email");
    t.data(&thi_sinh::sdt, "so_dien_thoai");
    t.data(&thi_sinh::ma_dinh_danh, "ma_dinh_danh");
}
}

thi_sinh::thi_sinh() {}
