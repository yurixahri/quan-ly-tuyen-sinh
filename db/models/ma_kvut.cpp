#include "ma_kvut.h"

QX_REGISTER_CPP(ma_kvut)

namespace qx {
template<> void register_class(QxClass<ma_kvut> & t)
{
    t.setName("ma_kvut");
    t.id(&ma_kvut::id, "id");
    t.data(&ma_kvut::ma, "ma");
    t.data(&ma_kvut::ten, "ten");
    t.data(&ma_kvut::diem, "diem");
}
}

ma_kvut::ma_kvut() {}
