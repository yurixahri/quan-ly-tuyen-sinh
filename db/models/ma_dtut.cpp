#include "ma_dtut.h"

QX_REGISTER_CPP(ma_dtut)

namespace qx {
template<> void register_class(QxClass<ma_dtut> & t)
{
    t.setName("ma_dtut");
    t.id(&ma_dtut::id, "id");
    t.data(&ma_dtut::ma, "ma");
    t.data(&ma_dtut::ten, "ten");
    t.data(&ma_dtut::diem, "diem");
}
}


ma_dtut::ma_dtut() {}
