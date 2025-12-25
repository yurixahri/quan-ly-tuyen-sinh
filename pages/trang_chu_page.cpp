#include "trang_chu_page.h"
#include <QtCharts>
#include <QDebug>
#include <QColor>

TrangChuDashboard::TrangChuDashboard(QWidget *parent)
    : QWidget(parent), chartViewThiSinh(nullptr), chartViewMaNganh(nullptr), 
      chartViewDangKy(nullptr), labelTongThiSinh(nullptr), 
      labelTongNganh(nullptr), labelTongDangKy(nullptr)
{
    initializeUI();
}

TrangChuDashboard::~TrangChuDashboard()
{
}

void TrangChuDashboard::initializeUI()
{
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Statistics Section
    QHBoxLayout *statsLayout = new QHBoxLayout();
    
    labelTongThiSinh = new QLabel("Tổng thí sinh: 0", this);
    labelTongThiSinh->setStyleSheet(
        "background-color: rgba(21, 83, 162, 224);"
        "color: rgb(240, 248, 255);"
        "padding: 15px;"
        "border-radius: 5px;"
        "font-weight: bold;"
        "font-size: 14px;"
    );

    labelTongNganh = new QLabel("Tổng ngành: 0", this);
    labelTongNganh->setStyleSheet(
        "background-color: rgba(0, 99, 54, 194);"
        "color: rgb(240, 248, 255);"
        "padding: 15px;"
        "border-radius: 5px;"
        "font-weight: bold;"
        "font-size: 14px;"
    );

    labelTongDangKy = new QLabel("Tổng đăng ký: 0", this);
    labelTongDangKy->setStyleSheet(
        "background-color: rgba(139, 69, 19, 194);"
        "color: rgb(240, 248, 255);"
        "padding: 15px;"
        "border-radius: 5px;"
        "font-weight: bold;"
        "font-size: 14px;"
    );

    statsLayout->addWidget(labelTongThiSinh);
    statsLayout->addWidget(labelTongNganh);
    statsLayout->addWidget(labelTongDangKy);
    statsLayout->addStretch();

    mainLayout->addLayout(statsLayout, 0, 0, 1, 2);

    // Chart 1: Thí sinh statistics (Pie Chart)
    chartViewThiSinh = new QChartView(this);
    chartViewThiSinh->setRenderHint(QPainter::Antialiasing);
    chartViewThiSinh->setStyleSheet(
        "background-color: rgba(0, 0, 0, 0);"
        "color: rgb(240, 248, 255);"
    );
    mainLayout->addWidget(chartViewThiSinh, 1, 0);

    // Chart 2: Ngành statistics (Pie Chart)
    chartViewMaNganh = new QChartView(this);
    chartViewMaNganh->setRenderHint(QPainter::Antialiasing);
    chartViewMaNganh->setStyleSheet(
        "background-color: rgba(0, 0, 0, 0);"
        "color: rgb(240, 248, 255);"
    );
    mainLayout->addWidget(chartViewMaNganh, 1, 1);

    // Chart 3: Đăng ký statistics (Bar Chart)
    chartViewDangKy = new QChartView(this);
    chartViewDangKy->setRenderHint(QPainter::Antialiasing);
    chartViewDangKy->setStyleSheet(
        "background-color: rgba(0, 0, 0, 0);"
        "color: rgb(240, 248, 255);"
    );
    mainLayout->addWidget(chartViewDangKy, 2, 0, 1, 2);

    this->setLayout(mainLayout);
}

void TrangChuDashboard::loadDashboardData()
{
    // Load Thí Sinh data
    createThiSinhChart();
    createMaNganhChart();
    createDangKyChart();
    createStatisticsLabels();
}

void TrangChuDashboard::createThiSinhChart()
{
    auto allThiSinh = getAllThiSinh();
    if (!allThiSinh || allThiSinh->empty()) {
        return;
    }

    // Create pie series - count students by gender or class
    QPieSeries *series = new QPieSeries();
    
    // Simple distribution chart
    QPieSlice *slice1 = new QPieSlice("Tổng thí sinh", allThiSinh->size());
    slice1->setColor(QColor(21, 83, 162));
    series->append(slice1);

    // Create chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Thống kê Thí Sinh");
    chart->setTitleBrush(QBrush(QColor(240, 248, 255)));
    chart->setBackgroundBrush(QBrush(QColor(0, 0, 0, 0)));
    chart->legend()->setLabelColor(QColor(240, 248, 255));

    chartViewThiSinh->setChart(chart);
}

void TrangChuDashboard::createMaNganhChart()
{
    auto allMaNganh = getAllMaNganh();
    if (!allMaNganh || allMaNganh->empty()) {
        return;
    }

    // Count mã ngành by nhóm ngành
    QMap<QString, int> nhomNganhCount;
    for (const auto &maNganh : *allMaNganh) {
        if (maNganh->nganh && maNganh->nganh->nhom_nganh) {
            nhomNganhCount[maNganh->nganh->nhom_nganh->ten]++;
        }
    }

    QPieSeries *series = new QPieSeries();
    QStringList colors = {"#1553A2", "#006336", "#8B4513", "#FF6347", "#4169E1"};
    int colorIndex = 0;

    for (auto it = nhomNganhCount.begin(); it != nhomNganhCount.end(); ++it) {
        QPieSlice *slice = new QPieSlice(it.key(), it.value());
        slice->setColor(QColor(colors[colorIndex % colors.size()]));
        series->append(slice);
        colorIndex++;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Thống kê Mã Ngành theo Nhóm Ngành");
    chart->setTitleBrush(QBrush(QColor(240, 248, 255)));
    chart->setBackgroundBrush(QBrush(QColor(0, 0, 0, 0)));
    chart->legend()->setLabelColor(QColor(240, 248, 255));

    chartViewMaNganh->setChart(chart);
}

void TrangChuDashboard::createDangKyChart()
{
    auto allDangKy = getAllDangKy();
    if (!allDangKy || allDangKy->empty()) {
        return;
    }

    // Count đăng ký by mã ngành
    QMap<QString, int> maNganhCount;
    for (const auto &dangKy : *allDangKy) {
        if (dangKy->ma_nganh && dangKy->ma_nganh->nganh) {
            QString maNganh = dangKy->ma_nganh->nganh->ma_nganh;
            maNganhCount[maNganh]++;
        }
    }

    // Create bar set
    QBarSet *set = new QBarSet("Số đăng ký");
    set->setColor(QColor(21, 83, 162));
    
    QStringList categories;
    for (auto it = maNganhCount.begin(); it != maNganhCount.end(); ++it) {
        *set << it.value();
        categories << it.key();
    }

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Thống kê Đăng Ký theo Mã Ngành");
    chart->setTitleBrush(QBrush(QColor(240, 248, 255)));
    chart->setBackgroundBrush(QBrush(QColor(0, 0, 0, 0)));
    chart->legend()->setLabelColor(QColor(240, 248, 255));

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsColor(QColor(240, 248, 255));
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelsColor(QColor(240, 248, 255));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chartViewDangKy->setChart(chart);
}

void TrangChuDashboard::createStatisticsLabels()
{
    auto allThiSinh = getAllThiSinh();
    auto allMaNganh = getAllMaNganh();
    auto allDangKy = getAllDangKy();

    if (allThiSinh) {
        labelTongThiSinh->setText(QString("Tổng thí sinh: %1").arg(allThiSinh->size()));
    }

    if (allMaNganh) {
        labelTongNganh->setText(QString("Tổng mã ngành: %1").arg(allMaNganh->size()));
    }

    if (allDangKy) {
        labelTongDangKy->setText(QString("Tổng đăng ký: %1").arg(allDangKy->size()));
    }
}
