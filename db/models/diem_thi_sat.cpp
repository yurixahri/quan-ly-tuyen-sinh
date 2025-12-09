#include "diem_thi_sat.h"

QX_REGISTER_CPP(diem_thi_sat)

namespace qx {
template<> void register_class(QxClass<diem_thi_sat> & t)
{
    t.setName("diem_thi_sat");
    t.id(&diem_thi_sat::id, "id_sat");
    t.data(&diem_thi_sat::diem, "diem");
    t.data(&diem_thi_sat::ma_dvtctdl, "ma_dvtctdl");
    t.data(&diem_thi_sat::ten_dvtctdl, "ten_dvtctdl");
    t.relationManyToOne(&diem_thi_sat::thi_sinh, "id_thi_sinh");
    t.relationManyToOne(&diem_thi_sat::ptxt, "id_ptxt");
}
}

diem_thi_sat::diem_thi_sat() {}
