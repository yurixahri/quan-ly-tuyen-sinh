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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
