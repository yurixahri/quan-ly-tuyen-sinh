#ifndef TRANG_CHU_PAGE_H
#define TRANG_CHU_PAGE_H

#include <QWidget>
#include <QtCharts>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QScrollArea>
#include "db/thi_sinh_dao.h"
#include "db/ma_nganh_dao.h"
#include "db/dang_ky_xet_tuyen_dao.h"

// Metric Card Widget
class MetricCard : public QFrame
{
    Q_OBJECT
public:
    explicit MetricCard(const QString &title, const QString &value, const QString &subtitle, 
                       const QColor &bgColor, const QString &icon, QWidget *parent = nullptr);
    void updateValue(const QString &newValue);
    void updateSubtitle(const QString &newSubtitle);

private:
    QLabel *labelValue;
    QLabel *labelSubtitle;
    QLabel *labelIcon;
    QLabel *labelTitle;
    void initializeUI();
};

class TrangChuDashboard : public QWidget
{
    Q_OBJECT
public:
    explicit TrangChuDashboard(QWidget *parent = nullptr);
    ~TrangChuDashboard();

    void loadDashboardData();

private:
    // Region 1: Key Metrics (4 cards)
    MetricCard *cardTongHoSo;
    MetricCard *cardNguyenVong;
    MetricCard *cardTyLeTrungTuyen;
    MetricCard *cardChiTieuConLai;

    // Region 2: Main Charts
    QChartView *chartViewTop10Nganh;  // Bar chart
    QChartView *chartViewPhuongThucXetTuyen; // Donut chart

    // Data storage
    QMap<QString, int> nganhDangKyMap;
    QMap<QString, int> ptxtMap;

    void initializeUI();
    void setupRegion1(QVBoxLayout *mainLayout);
    void setupRegion2(QVBoxLayout *mainLayout);

    void loadMetricsData();
    void createTop10NganhChart();
    void createPhuongThucXetTuyenChart();

    void calculateNganhDangKyMap();
    void calculatePtxtMap();
};

#endif // TRANG_CHU_PAGE_H
