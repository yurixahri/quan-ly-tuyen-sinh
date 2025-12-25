#include "trang_chu_page.h"
#include <QtCharts>
#include <QDebug>
#include <QColor>
#include <QFont>
#include <cmath>

// ========== MetricCard Implementation ==========
MetricCard::MetricCard(const QString &title, const QString &value, const QString &subtitle,
                       const QColor &bgColor, const QString &icon, QWidget *parent)
    : QFrame(parent), labelValue(nullptr), labelSubtitle(nullptr), labelIcon(nullptr), labelTitle(nullptr)
{
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Raised);
    setLineWidth(0);
    
    // Set background color
    QString bgStyle = QString(
        "background-color: %1;"
        "border-radius: 8px;"
        "padding: 15px;"
        "border: none;"
    ).arg(bgColor.name());
    setStyleSheet(bgStyle);
    setMinimumHeight(180);
    setMaximumHeight(220);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(12, 12, 12, 12);
    layout->setSpacing(3);
    layout->setAlignment(Qt::AlignCenter);
    
    // Icon
    labelIcon = new QLabel(icon);
    labelIcon->setFont(QFont("Arial", 24));
    labelIcon->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    labelIcon->setStyleSheet("color: rgb(240, 248, 255);");
    
    // Title
    labelTitle = new QLabel(title);
    labelTitle->setFont(QFont("Arial", 11));
    labelTitle->setStyleSheet("color: rgba(240, 248, 255, 180); background: transparent;");
    labelTitle->setWordWrap(true);
    
    // Value
    labelValue = new QLabel(value);
    labelValue->setFont(QFont("Arial", 28, QFont::Bold));
    labelValue->setStyleSheet("color: rgb(240, 248, 255); background: transparent;");
    labelValue->setWordWrap(true);
    
    // Subtitle
    labelSubtitle = new QLabel(subtitle);
    labelSubtitle->setFont(QFont("Arial", 10));
    labelSubtitle->setStyleSheet("color: rgba(240, 248, 255, 160); background: transparent;");
    labelSubtitle->setWordWrap(true);
    
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->addWidget(labelIcon);
    topLayout->addStretch();
    
    layout->addLayout(topLayout);
    layout->addWidget(labelTitle);
    layout->addWidget(labelValue);
    if (!subtitle.isEmpty()) {
        layout->addWidget(labelSubtitle);
    }
    layout->addStretch();
    
    setLayout(layout);
}

void MetricCard::updateValue(const QString &newValue)
{
    if (labelValue) {
        labelValue->setText(newValue);
    }
}

void MetricCard::updateSubtitle(const QString &newSubtitle)
{
    if (labelSubtitle) {
        labelSubtitle->setText(newSubtitle);
    }
}

// ========== TrangChuDashboard Implementation ==========
TrangChuDashboard::TrangChuDashboard(QWidget *parent)
    : QWidget(parent),
      cardTongHoSo(nullptr), cardNguyenVong(nullptr),
      cardTyLeTrungTuyen(nullptr), cardChiTieuConLai(nullptr),
      chartViewTop10Nganh(nullptr), chartViewPhuongThucXetTuyen(nullptr)
{
    setStyleSheet("background-color: rgb(30, 30, 30);");
    initializeUI();
}

TrangChuDashboard::~TrangChuDashboard()
{
}

void TrangChuDashboard::initializeUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(20);
    
    setupRegion1(mainLayout);
    setupRegion2(mainLayout);
    
    mainLayout->addStretch();
    setLayout(mainLayout);
}

void TrangChuDashboard::setupRegion1(QVBoxLayout *mainLayout)
{
    QLabel *titleRegion1 = new QLabel("📊 Chỉ Số Chính");
    titleRegion1->setFont(QFont("Arial", 16, QFont::Bold));
    titleRegion1->setStyleSheet("color: rgb(240, 248, 255); margin-bottom: 10px;");
    
    QWidget *region1Widget = new QWidget();
    QVBoxLayout *region1Layout = new QVBoxLayout(region1Widget);
    region1Layout->setContentsMargins(0, 0, 0, 0);
    region1Layout->setSpacing(15);
    
    region1Layout->addWidget(titleRegion1);
    
    // 4 Metric Cards
    QHBoxLayout *cardsLayout = new QHBoxLayout();
    cardsLayout->setSpacing(15);
    cardsLayout->setContentsMargins(0, 0, 0, 0);
    
    // Card 1: Tổng Hồ sơ
    cardTongHoSo = new MetricCard(
        "Tổng Hồ Sơ",
        "0",
        "",
        QColor(21, 83, 162),  // Blue
        "👤"
    );
    
    // Card 2: Tổng Nguyện vọng
    cardNguyenVong = new MetricCard(
        "Tổng Nguyện Vọng",
        "0",
        "Trung bình: 0 NV/Thí sinh",
        QColor(255, 140, 0),  // Orange
        "📋"
    );
    
    // Card 3: Tỷ lệ Trúng tuyển
    cardTyLeTrungTuyen = new MetricCard(
        "Tỷ Lệ Trúng Tuyển",
        "0%",
        "",
        QColor(34, 139, 34),  // Green
        "✓"
    );
    
    // Card 4: Tổng chỉ tiêu còn lại
    cardChiTieuConLai = new MetricCard(
        "Chỉ Tiêu Còn Lại",
        "0 / 0",
        "",
        QColor(178, 34, 34),  // Red
        "⚠"
    );
    
    cardsLayout->addWidget(cardTongHoSo);
    cardsLayout->addWidget(cardNguyenVong);
    cardsLayout->addWidget(cardTyLeTrungTuyen);
    cardsLayout->addWidget(cardChiTieuConLai);
    
    region1Layout->addLayout(cardsLayout);
    
    if (mainLayout) {
        mainLayout->addWidget(region1Widget);
    }
}

void TrangChuDashboard::setupRegion2(QVBoxLayout *mainLayout)
{
    QLabel *titleRegion2 = new QLabel("🎯 Trọng Tâm Tuyển Sinh");
    titleRegion2->setFont(QFont("Arial", 16, QFont::Bold));
    titleRegion2->setStyleSheet("color: rgb(240, 248, 255); margin-bottom: 10px;");
    
    QWidget *region2Widget = new QWidget();
    QVBoxLayout *region2Layout = new QVBoxLayout(region2Widget);
    region2Layout->setContentsMargins(0, 0, 0, 0);
    region2Layout->setSpacing(15);
    
    region2Layout->addWidget(titleRegion2);
    
    QHBoxLayout *chartsLayout = new QHBoxLayout();
    chartsLayout->setSpacing(15);
    chartsLayout->setContentsMargins(0, 0, 0, 0);
    
    // Left: Top 10 Ngành (Bar Chart) - 2/3 width
    chartViewTop10Nganh = new QChartView(this);
    chartViewTop10Nganh->setRenderHint(QPainter::Antialiasing);
    chartViewTop10Nganh->setStyleSheet(
        "QChartView {"
        "  background-color: rgb(45, 45, 45);"
        "  border-radius: 8px;"
        "  border: 1px solid rgb(60, 60, 60);"
        "}"
    );
    chartViewTop10Nganh->setMinimumHeight(420);
    chartsLayout->addWidget(chartViewTop10Nganh, 2);
    
    // Right: Phương thức xét tuyển (Donut Chart) - 1/3 width
    chartViewPhuongThucXetTuyen = new QChartView(this);
    chartViewPhuongThucXetTuyen->setRenderHint(QPainter::Antialiasing);
    chartViewPhuongThucXetTuyen->setStyleSheet(
        "QChartView {"
        "  background-color: rgb(45, 45, 45);"
        "  border-radius: 8px;"
        "  border: 1px solid rgb(60, 60, 60);"
        "}"
    );
    chartViewPhuongThucXetTuyen->setMinimumHeight(420);
    chartsLayout->addWidget(chartViewPhuongThucXetTuyen, 1);
    
    region2Layout->addLayout(chartsLayout);
    
    if (mainLayout) {
        mainLayout->addWidget(region2Widget);
    }
}



void TrangChuDashboard::loadDashboardData()
{
    calculateNganhDangKyMap();
    calculatePtxtMap();
    
    loadMetricsData();
    createTop10NganhChart();
    createPhuongThucXetTuyenChart();
}

void TrangChuDashboard::loadMetricsData()
{
    auto allThiSinh = getAllThiSinh();
    auto allDangKy = getAllDangKy();
    
    int totalThiSinh = 0;
    int totalDangKy = 0;
    
    if (allThiSinh && !allThiSinh->empty()) {
        totalThiSinh = allThiSinh->size();
    } else {
        qWarning() << "No thi_sinh data available";
    }
    
    if (allDangKy && !allDangKy->empty()) {
        totalDangKy = allDangKy->size();
    } else {
        qWarning() << "No dang_ky data available";
    }
    
    qDebug() << "Metrics: " << totalThiSinh << " thi sinh, " << totalDangKy << " dang ky";
    
    // Update Card 1: Tổng Hồ sơ
    if (cardTongHoSo) {
        cardTongHoSo->updateValue(QString::number(totalThiSinh));
    }
    
    // Update Card 2: Tổng Nguyện vọng
    if (cardNguyenVong) {
        cardNguyenVong->updateValue(QString::number(totalDangKy));
        if (totalThiSinh > 0) {
            double avg = static_cast<double>(totalDangKy) / totalThiSinh;
            cardNguyenVong->updateSubtitle(QString("Trung bình: %1 NV/Thí sinh").arg(avg, 0, 'f', 1));
        } else {
            cardNguyenVong->updateSubtitle("Trung bình: 0 NV/Thí sinh");
        }
    }
    
    // Update Card 3: Tỷ lệ Trúng tuyển
    if (cardTyLeTrungTuyen && allDangKy) {
        int successCount = 0;
        for (const auto &dk : *allDangKy) {
            if (dk && !dk->trang_thai.isEmpty() && dk->trang_thai.toLower() == "trúng tuyển") {
                successCount++;
            }
        }
        
        double percentage = 0;
        if (totalThiSinh > 0) {
            percentage = (static_cast<double>(successCount) / totalThiSinh) * 100;
        }
        cardTyLeTrungTuyen->updateValue(QString("%1%").arg(static_cast<int>(percentage)));
    }
    
    // Update Card 4: Tổng chỉ tiêu còn lại
    if (cardChiTieuConLai) {
        auto allMaNganh = getAllMaNganh();
        int totalChiTieu = 0;
        int usedChiTieu = 0;
        
        if (allMaNganh) {
            for (const auto &mn : *allMaNganh) {
                if (mn) {
                    totalChiTieu += mn->chi_tieu;
                    
                    if (mn->nganh && nganhDangKyMap.contains(mn->nganh->ten_nganh)) {
                        usedChiTieu += nganhDangKyMap[mn->nganh->ten_nganh];
                    }
                }
            }
        }
        
        int remaining = totalChiTieu - usedChiTieu;
        remaining = (remaining < 0) ? 0 : remaining;
        cardChiTieuConLai->updateValue(QString("%1 / %2").arg(remaining).arg(totalChiTieu));
    }
}

void TrangChuDashboard::calculateNganhDangKyMap()
{
    nganhDangKyMap.clear();
    auto allDangKy = getAllDangKy();
    
    if (!allDangKy) {
        qWarning() << "getAllDangKy returned nullptr";
        return;
    }
    
    if (allDangKy->empty()) {
        qWarning() << "getAllDangKy returned empty list";
        return;
    }
    
    auto allMaNganh = getAllMaNganh();
    
    for (const auto &dk : *allDangKy) {
        if (!dk) {
            continue;
        }
        
        if (!dk->ma_nganh) {
            continue;
        }
        
        // Use the ma_nganh->nganh relationship, but with fallback
        QString tenNganh;
        
        if (dk->ma_nganh->nganh && !dk->ma_nganh->nganh->ten_nganh.trimmed().isEmpty()) {
            tenNganh = dk->ma_nganh->nganh->ten_nganh.trimmed();
        } else {
            // Fallback: try to find from allMaNganh
            if (allMaNganh) {
                for (const auto &mn : *allMaNganh) {
                    if (mn && mn->id == dk->ma_nganh->id) {
                        if (mn->nganh && !mn->nganh->ten_nganh.trimmed().isEmpty()) {
                            tenNganh = mn->nganh->ten_nganh.trimmed();
                        }
                        break;
                    }
                }
            }
        }
        
        if (tenNganh.isEmpty()) {
            // Last resort: use ma_nganh id as placeholder
            tenNganh = QString("Ngành #%1").arg(dk->ma_nganh->id);
        }
        
        nganhDangKyMap[tenNganh]++;
    }
    
    qDebug() << "calculateNganhDangKyMap: " << nganhDangKyMap.size() << " nganh loaded";
    for (auto it = nganhDangKyMap.begin(); it != nganhDangKyMap.end(); ++it) {
        qDebug() << "  " << it.key() << ": " << it.value();
    }
}

void TrangChuDashboard::calculatePtxtMap()
{
    ptxtMap.clear();
    auto allDangKy = getAllDangKy();
    
    if (!allDangKy) {
        qWarning() << "getAllDangKy returned nullptr";
        return;
    }
    
    if (allDangKy->empty()) {
        qWarning() << "getAllDangKy returned empty list";
        return;
    }
    
    for (const auto &dk : *allDangKy) {
        if (!dk) {
            continue;
        }
        
        if (!dk->ptxt) {
            // ptxt may be null, which is ok
            continue;
        }
        
        QString tenPtxt = dk->ptxt->ten.trimmed();
        if (tenPtxt.isEmpty()) {
            qWarning() << "ten of ptxt is empty";
            continue;
        }
        
        ptxtMap[tenPtxt]++;
    }
    
    qDebug() << "calculatePtxtMap: " << ptxtMap.size() << " phuong thuc loaded";
    for (auto it = ptxtMap.begin(); it != ptxtMap.end(); ++it) {
        qDebug() << "  " << it.key() << ": " << it.value();
    }
}



void TrangChuDashboard::createTop10NganhChart()
{
    if (nganhDangKyMap.empty()) {
        qCritical() << "ERROR: nganhDangKyMap is empty! No data for Top10 Nganh chart";
        
        // Show empty chart with message
        QChart *chart = new QChart();
        chart->setTitle("Top 10 Ngành Có Lượng Đăng Ký Cao Nhất - [Chưa Có Dữ Liệu]");
        chart->setTitleBrush(QBrush(QColor(240, 248, 255)));
        chart->setBackgroundBrush(QBrush(QColor(45, 45, 45)));
        
        if (chartViewTop10Nganh) {
            chartViewTop10Nganh->setChart(chart);
        }
        return;
    }
    
    qDebug() << "Creating Top10 chart with" << nganhDangKyMap.size() << "nganh";
    
    // Sort by value (descending) and take top 10
    QVector<QPair<QString, int>> sortedNganh;
    for (auto it = nganhDangKyMap.begin(); it != nganhDangKyMap.end(); ++it) {
        sortedNganh.append({it.key(), it.value()});
    }
    std::sort(sortedNganh.begin(), sortedNganh.end(),
              [](const auto &a, const auto &b) { return a.second > b.second; });
    
    int limit = qMin(10, sortedNganh.size());
    sortedNganh.erase(sortedNganh.begin() + limit, sortedNganh.end());
    
    qDebug() << "Showing top" << sortedNganh.size() << "nganh";
    
    // Reverse for horizontal display (top item at bottom visually)
    std::reverse(sortedNganh.begin(), sortedNganh.end());
    
    // Create bar set
    QBarSet *set = new QBarSet("Số Đăng Ký");
    set->setColor(QColor(30, 144, 255));
    
    QStringList categories;
    for (int i = 0; i < sortedNganh.size(); ++i) {
        *set << sortedNganh[i].second;
        categories << sortedNganh[i].first;
        qDebug() << "  Bar" << (i+1) << ": " << sortedNganh[i].first << " = " << sortedNganh[i].second;
    }
    
    QBarSeries *series = new QBarSeries();
    series->append(set);
    
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Top 10 Ngành Có Lượng Đăng Ký Cao Nhất");
    chart->setTitleBrush(QBrush(QColor(240, 248, 255)));
    chart->setBackgroundBrush(QBrush(QColor(45, 45, 45)));
    chart->setMargins(QMargins(20, 30, 20, 20));
    chart->setAnimationOptions(QChart::SeriesAnimations);
    
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsColor(QColor(200, 200, 200));
    axisX->setLabelsFont(QFont("Arial", 10));
    axisX->setTitleText("");
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    
    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelsColor(QColor(200, 200, 200));
    axisY->setLabelsFont(QFont("Arial", 10));
    axisY->setGridLineVisible(true);
    axisY->setGridLineColor(QColor(60, 60, 60));
    axisY->setTitleText("Số Lượng");
    axisY->setTitleBrush(QBrush(QColor(200, 200, 200)));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setLabelColor(QColor(200, 200, 200));
    chart->legend()->setMarkerShape(QLegend::MarkerShapeRectangle);
    
    if (chartViewTop10Nganh) {
        chartViewTop10Nganh->setChart(chart);
        chartViewTop10Nganh->setRenderHint(QPainter::Antialiasing);
    }
}

void TrangChuDashboard::createPhuongThucXetTuyenChart()
{
    if (ptxtMap.empty()) {
        qCritical() << "ERROR: ptxtMap is empty! No data for Phuong Thuc Xet Tuyen chart";
        
        // Show empty chart with message
        QChart *chart = new QChart();
        chart->setTitle("Cơ Cấu Theo Phương Thức Xét Tuyển - [Chưa Có Dữ Liệu]");
        chart->setTitleBrush(QBrush(QColor(240, 248, 255)));
        chart->setBackgroundBrush(QBrush(QColor(45, 45, 45)));
        
        if (chartViewPhuongThucXetTuyen) {
            chartViewPhuongThucXetTuyen->setChart(chart);
        }
        return;
    }
    
    qDebug() << "Creating Phuong Thuc chart with" << ptxtMap.size() << "methods";
    
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);  // Create donut chart
    
    QStringList colors = {
        "#FF6347",  // Tomato
        "#4169E1",  // Royal Blue
        "#32CD32",  // Lime Green
        "#FFD700",  // Gold
        "#FF8C00",  // Dark Orange
        "#00CED1",  // Dark Turquoise
        "#FFB6C1"   // Light Pink
    };
    
    int colorIndex = 0;
    double totalCount = 0;
    
    // Calculate total
    for (auto it = ptxtMap.begin(); it != ptxtMap.end(); ++it) {
        totalCount += it.value();
    }
    
    qDebug() << "Total dang ky:" << static_cast<int>(totalCount);
    
    // Add slices
    for (auto it = ptxtMap.begin(); it != ptxtMap.end(); ++it) {
        qDebug() << "  " << it.key() << ":" << it.value();
        
        QPieSlice *slice = new QPieSlice(it.key(), it.value());
        slice->setColor(QColor(colors[colorIndex % colors.size()]));
        slice->setLabelVisible(true);
        slice->setLabelPosition(QPieSlice::LabelOutside);
        slice->setLabelArmLengthFactor(1.2);
        
        // Set percentage label
        double percentage = (it.value() / totalCount) * 100;
        QString label = QString("%1\n(%2%)")
                        .arg(it.key())
                        .arg(percentage, 0, 'f', 1);
        slice->setLabel(label);
        slice->setLabelFont(QFont("Arial", 9));
        
        series->append(slice);
        colorIndex++;
    }
    
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Cơ Cấu Theo Phương Thức Xét Tuyển");
    chart->setTitleBrush(QBrush(QColor(240, 248, 255)));
    chart->setBackgroundBrush(QBrush(QColor(45, 45, 45)));
    chart->setMargins(QMargins(20, 30, 20, 20));
    chart->setAnimationOptions(QChart::SeriesAnimations);
    
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setLabelColor(QColor(200, 200, 200));
    chart->legend()->setFont(QFont("Arial", 9));
    
    if (chartViewPhuongThucXetTuyen) {
        chartViewPhuongThucXetTuyen->setChart(chart);
        chartViewPhuongThucXetTuyen->setRenderHint(QPainter::Antialiasing);
    }
}




