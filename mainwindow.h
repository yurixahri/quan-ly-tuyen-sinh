#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // mon hoc
    void on_monhoc_button_clicked();
    void on_add_monhoc_button_clicked();
    void monHocTableContextMenu(const QPoint& pos);
    void updateMonHoc(long id);
    void deleteMonHoc(long id);


    void on_tohop_button_clicked();
    void on_add_tohop_button_clicked();
    void on_tohop_mon_table_customContextMenuRequested(const QPoint &pos);
    void updateToHop(long id);
    void deleteToHop(long id);

    void on_add_nhom_nganh_button_clicked();
    void on_nhom_nganh_button_clicked();
    void on_nhom_nganh_table_customContextMenuRequested(const QPoint &pos);
    void updateNhomNganh(long id);
    void deleteNhomNganh(long id);


    void on_nganh_button_clicked();
    void on_add_nganh_button_clicked();
    void on_nganh_table_customContextMenuRequested(const QPoint &pos);
    void updateNganh(long id);
    void deleteNganh(long id);

    void on_ma_nganh_button_clicked();
    void on_add_ma_nganh_button_clicked();
    void on_ma_nganh_table_customContextMenuRequested(const QPoint &pos);
    void updateMaNganh(long id);
    void deleteMaNganh(long id);

    void on_ptxt_button_clicked();
    void on_add_ptxt_button_clicked();
    void on_ptxt_table_customContextMenuRequested(const QPoint &pos);
    void updatePtxt(long id);
    void deletePtxt(long id);

    void on_add_thi_sinh_button_clicked();
    void on_thi_sinh_button_clicked();
    void on_thi_sinh_table_customContextMenuRequested(const QPoint &pos);
    void updateThiSinh(long id);
    void deleteThiSinh(long id);
    void thiSinhDetail(long id);

    void on_delete_all_ma_nganh_clicked();
    void on_delete_all_tohop_clicked();
    void on_delete_all_monhoc_clicked();
    void on_import_tohop_clicked();
    void on_import_ptxt_clicked();
    void on_thi_sinh_current_page_editingFinished();
    void on_thi_sinh_previous_page_clicked();
    void on_thi_sinh_next_page_clicked();
    void resetMaxThiSinhPageCount();

    void on_ma_nganh_import_excel_clicked();
    void on_export_ma_nganh_button_clicked();
    void on_import_sat_button_clicked();
    void on_close_clicked();
    void on_import_ccnn_button_clicked();
    void on_import_hocba_button_clicked();

    void on_thi_sinh_current_page_valueChanged(int arg1);

    void on_add_ccnn_button_clicked();
    void on_ccnn_table_customContextMenuRequested(const QPoint &pos);
    void updateMaChungchinn(long id);
    void deleteMaChungchinn(long id);

    void on_add_thanh_tich_button_clicked();
    void on_thanh_tich_table_customContextMenuRequested(const QPoint &pos);
    void updateMaThanhTich(long id);
    void deleteMaThanhTich(long id);

    void on_add_dtut_button_clicked();
    void on_dtut_table_customContextMenuRequested(const QPoint &pos);
    void updateMaDtut(long id);
    void deleteMaDtut(long id);

    void on_add_kvut_button_clicked();
    void on_kvut_table_customContextMenuRequested(const QPoint &pos);
    void updateMaKvut(long id);
    void deleteMaKvut(long id);

    void on_ccnn_button_clicked();
    void on_thanh_tich_button_clicked();
    void on_dtut_button_clicked();
    void on_kvut_button_clicked();

    void on_import_doatgiai_button_clicked();

    void on_thi_sinh_tim_kiem_editingFinished();

    void on_import_uutien_button_clicked();

    void on_import_dkxt_button_clicked();

private:
    Ui::MainWindow *ui;
    bool m_dragging = false;
    QPoint m_dragPosition;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};
#endif // MAINWINDOW_H
