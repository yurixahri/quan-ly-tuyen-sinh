#ifndef THI_SINH_DETAIL_H
#define THI_SINH_DETAIL_H

#include <QDialog>
#include "db/models/thi_sinh.h"

namespace Ui {
class thi_sinh_detail;
}

class thi_sinh_detail : public QDialog
{
    Q_OBJECT

public:
    explicit thi_sinh_detail(QWidget *parent = nullptr);
    ~thi_sinh_detail();

    thi_sinh_ptr item;
    void setThiSinh(thi_sinh_ptr item);
private slots:
    void fillDoatGiaiTable();
    void fillDiemSatTable();
    void fillDiemHocbaTable();
    void fillChungchiTienganhTable();

    void on_diem_hocba_table_customContextMenuRequested(const QPoint &pos);
    void on_diem_sat_table_customContextMenuRequested(const QPoint &pos);
    void on_thanh_tich_table_customContextMenuRequested(const QPoint &pos);
    void on_ccnn_table_customContextMenuRequested(const QPoint &pos);

    void updateDoatGiai(long id);
    void deleteDoatGiai(long id);


    void updateDiemSat(long id);
    void deleteDiemSat(long id);


    void updateDiemHocba(long id);
    void deleteDiemHocba(long id);

    void updateChungchiTienganh(long id);
    void deleteChungchiTienganh(long id);

    void on_add_diem_sat_button_clicked();
    void on_add_ccnn_button_clicked();
    void on_add_thanh_tich_button_clicked();
    void on_add_diem_hocba_button_clicked();

    void on_close_clicked();

private:
    Ui::thi_sinh_detail *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // THI_SINH_DETAIL_H
