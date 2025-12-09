#include "ma_chungchinn.h"

QX_REGISTER_CPP(ma_chungchinn)

namespace qx {
template<> void register_class(QxClass<ma_chungchinn> & t)
{
    t.setName("ma_chungchinn");
    t.id(&ma_chungchinn::id, "id");
    t.data(&ma_chungchinn::ma, "ma_ccnn");
    t.data(&ma_chungchinn::ten, "ten_ccnn");
}
}

ma_chungchinn::ma_chungchinn() {}
