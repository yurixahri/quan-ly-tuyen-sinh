#include "ptxt.h"

QX_REGISTER_CPP(ptxt)

namespace qx {
template<> void register_class(QxClass<ptxt> & t)
{
    t.setName("phuongthuc_xettuyen");
    t.id(&ptxt::id, "id_phuongthuc");
    t.data(&ptxt::ma, "ma_xettuyen");
    t.data(&ptxt::ten, "ten_phuongthuc");
    t.data(&ptxt::thang_diem, "thang_diem");
    t.data(&ptxt::mo_ta, "mo_ta");
}
}

ptxt::ptxt() {}
