#ifndef DIEM_THI_SAT_DAO_H
#define DIEM_THI_SAT_DAO_H

#include "db/models/diem_thi_sat.h"
#include "utils/string.h"
#include "excel/read_excel.h"

inline bool addDiemThiSat(long &id_thi_sinh, long &id_ptxt, float &diem,
                          QString &ma_dvtctdl, QString &ten_dvtctdl){
    diem_thi_sat_ptr adding;
    adding.reset(new diem_thi_sat());
    adding->thi_sinh = std::make_shared<thi_sinh>(id_thi_sinh);
    adding->ptxt = std::make_shared<ptxt>(id_ptxt);
    adding->diem = diem;
    adding->ma_dvtctdl = ma_dvtctdl;
    adding->ten_dvtctdl = ten_dvtctdl;

    trimLeadingAndTrailing(adding->ma_dvtctdl);
    trimLeadingAndTrailing(adding->ten_dvtctdl);

    if (adding->ma_dvtctdl.isEmpty() || adding->ten_dvtctdl.isEmpty())
        return false;

    if (diem < 0.0f)
        return false;

    QSqlError err = qx::dao::insert(adding);
    if (err.isValid())
        return false;
    else
        return true;
}

inline bool changeDiemThiSat(diem_thi_sat_ptr &item, long &id_ptxt, float &diem,
                             QString &ma_dvtctdl, QString &ten_dvtctdl){
    item->diem = diem;
    item->ma_dvtctdl = ma_dvtctdl;
    item->ten_dvtctdl = ten_dvtctdl;
    item->ptxt = std::make_shared<ptxt>(id_ptxt);

    trimLeadingAndTrailing(item->ma_dvtctdl);
    trimLeadingAndTrailing(item->ten_dvtctdl);

    if (item->ma_dvtctdl.isEmpty() || item->ten_dvtctdl.isEmpty())
        return false;

    if (diem < 0.0f)
        return false;

    QSqlError err = qx::dao::update(item);
    if (err.isValid())
        return false;
    else
        return true;
}

inline std::optional<diem_thi_sat_ptr> getDiemThiSatById(long &id){
    diem_thi_sat_ptr item;
    item.reset(new diem_thi_sat(id));
    QSqlError err = qx::dao::fetch_by_id(item);
    if (err.isValid())
        return std::nullopt;
    else
        return item;
}

inline std::optional<QList<diem_thi_sat_ptr>> getDiemThiSatByThiSinhId(long &id_thi_sinh){
    QList<diem_thi_sat_ptr> list;
    qx_query query;
    query.where("diem_thi_sat.id_thi_sinh").isEqualTo(QVariant::fromValue(id_thi_sinh));
    QSqlError err = qx::dao::fetch_by_query_with_all_relation(query, list);
    if (err.isValid())
        return std::nullopt;
    else
        return list;
}

inline std::optional<QList<diem_thi_sat_ptr>> getAllDiemThiSat(){
    QList<diem_thi_sat_ptr> list;
    qx_query query;
    // query.orderAsc("");
    QSqlError err = qx::dao::fetch_by_query_with_all_relation(query, list);
    if (err.isValid())
        return std::nullopt;
    else
        return list;
}

inline bool deleteDiemThiSatById(long &id){
    diem_thi_sat_ptr item;
    item.reset(new diem_thi_sat(id));
    QSqlError err = qx::dao::delete_by_id(item);
    if (err.isValid())
        return false;
    else
        return true;
}

inline bool exportDiemSatToExcel(QString &path){
    auto list_opt = getAllDiemThiSat();
    if (!list_opt) return false;
    auto list = *list_opt;

    QXlsx::Document xlsx;
    // Title
    int row = 1;
    xlsx.write(row, 1, "BẢNG ĐIỂM THI SAT CỦA THÍ SINH");
    xlsx.mergeCells("A1:L1");
    // Header
    ++row;
    xlsx.write(row, 1, "STT");
    xlsx.write(row, 2, "Họ Tên");
    xlsx.write(row, 3, "CMND/CCCD");
    xlsx.write(row, 4, "Ngày sinh");
    xlsx.write(row, 5, "Giới tính");
    xlsx.write(row, 6, "Điểm");
    xlsx.write(row, 7, "MADVTCTDL");
    xlsx.write(row, 8, "TENDVTCTDL");
    xlsx.write(row, 9, "PTXT");
    xlsx.write(row, 10, "Thành tích");
    xlsx.write(row, 11, "Môn đạt giải");
    xlsx.write(row, 12, "Điểm cộng");

    for (auto &item : list){
        ++row;

        xlsx.write(row, 1, row-2);
        xlsx.write(row, 2, item->thi_sinh->ho_ten);
        xlsx.write(row, 3, item->thi_sinh->cccd);
        xlsx.write(row, 4, item->thi_sinh->ngay_sinh.toString("dd/MM/yyyy"));
        xlsx.write(row, 5, item->thi_sinh->gioi_tinh);
        xlsx.write(row, 6, item->diem);
        xlsx.write(row, 7, item->ma_dvtctdl);
        xlsx.write(row, 8, item->ten_dvtctdl);
        xlsx.write(row, 9, item->ptxt ? item->ptxt->ma : "");
    }

    return xlsx.saveAs(path);
}
#endif // DIEM_THI_SAT_DAO_H
