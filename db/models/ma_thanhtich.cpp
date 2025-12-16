#include "ma_thanhtich.h"

QX_REGISTER_CPP(ma_thanhtich)

namespace qx {
template<> void register_class(QxClass<ma_thanhtich> & t)
{
    t.setName("ma_thanhtich");
    t.id(&ma_thanhtich::id, "id");
    t.data(&ma_thanhtich::ma, "ma");
    t.data(&ma_thanhtich::ten, "ten");
    t.data(&ma_thanhtich::diem, "diem_cong");
}
}

ma_thanhtich::ma_thanhtich() {}
