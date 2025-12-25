#ifndef TRANG_CHU_PAGE_H
#define TRANG_CHU_PAGE_H

#include <QWidget>
#include <QtCharts>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include "db/thi_sinh_dao.h"
#include "db/ma_nganh_dao.h"
#include "db/dang_ky_xet_tuyen_dao.h"

class TrangChuDashboard : public QWidget
{
    Q_OBJECT
public:
    explicit TrangChuDashboard(QWidget *parent = nullptr);
    ~TrangChuDashboard();

    void loadDashboardData();

private:
    QChartView *chartViewThiSinh;
    QChartView *chartViewMaNganh;
    QChartView *chartViewDangKy;
    QLabel *labelTongThiSinh;
    QLabel *labelTongNganh;
    QLabel *labelTongDangKy;

    void initializeUI();
    void createThiSinhChart();
    void createMaNganhChart();
    void createDangKyChart();
    void createStatisticsLabels();
};

#endif // TRANG_CHU_PAGE_H
