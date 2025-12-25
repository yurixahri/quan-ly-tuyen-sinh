#include "ma_nganh_import_dialog.h"
#include <QTabWidget>
#include <QHeaderView>
#include <QColor>

ma_nganh_import_dialog::ma_nganh_import_dialog(std::optional<QList<QStringList>> data, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Xem trước và kiểm tra dữ liệu import");
    setGeometry(100, 100, 1000, 600);
    
    if (data.has_value()){
        m_rawData = data.value();
        validateAndDisplayData(m_rawData);
        setupUI();
    }
}

ma_nganh_import_dialog::~ma_nganh_import_dialog()
{
}

void ma_nganh_import_dialog::validateAndDisplayData(const QList<QStringList> &data)
{
    // Step 2: Pre-process data (trim and remove empty rows)
    m_preprocessedData = MaNganhImportValidator::preprocessData(data);
    
    // Step 3: Validate each row
    m_validatedRows = MaNganhImportValidator::validateRows(m_preprocessedData);
    
    // Count valid and error rows
    m_validRowCount = 0;
    m_errorRowCount = 0;
    for (const auto &row : m_validatedRows){
        if (row.isValid){
            m_validRowCount++;
        } else {
            m_errorRowCount++;
        }
    }
}

void ma_nganh_import_dialog::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Summary label
    summaryLabel = new QLabel();
    QString summary = QString("Tổng: %1 dòng | ✓ Hợp lệ: %2 dòng | ✗ Lỗi: %3 dòng")
        .arg(m_validatedRows.length())
        .arg(m_validRowCount)
        .arg(m_errorRowCount);
    summaryLabel->setText(summary);
    summaryLabel->setStyleSheet("QLabel { font-weight: bold; padding: 10px; background-color: #f0f0f0; border-radius: 3px; }");
    mainLayout->addWidget(summaryLabel);
    
    // Tab widget for valid and error data
    QTabWidget *tabs = new QTabWidget();
    
    // Create tabs
    createValidDataTab(tabs);
    if (m_errorRowCount > 0){
        createErrorDataTab(tabs);
    }
    
    mainLayout->addWidget(tabs);
    
    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    importBtn = new QPushButton("Import");
    cancelBtn = new QPushButton("Hủy");
    
    // Disable import if there are no valid rows
    if (m_validRowCount == 0){
        importBtn->setEnabled(false);
        importBtn->setToolTip("Không có dữ liệu hợp lệ để import");
    }
    
    connect(importBtn, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelBtn, &QPushButton::clicked, this, &QDialog::reject);
    
    buttonLayout->addStretch();
    buttonLayout->addWidget(importBtn);
    buttonLayout->addWidget(cancelBtn);
    mainLayout->addLayout(buttonLayout);
    
    setLayout(mainLayout);
}

void ma_nganh_import_dialog::createValidDataTab(QTabWidget *tabs)
{
    QWidget *validWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(validWidget);
    
    validTable = new QTableWidget();
    validTable->setColumnCount(5);
    validTable->setHorizontalHeaderLabels({"STT", "MÃ NGÀNH", "NGÀNH", "NHÓM NGÀNH", "TỔ HỢP"});
    
    populateValidTable();
    
    validTable->resizeColumnsToContents();
    validTable->horizontalHeader()->setStretchLastSection(true);
    
    layout->addWidget(validTable);
    validWidget->setLayout(layout);
    
    tabs->addTab(validWidget, QString("Dữ liệu hợp lệ (%1)").arg(m_validRowCount));
}

void ma_nganh_import_dialog::createErrorDataTab(QTabWidget *tabs)
{
    QWidget *errorWidget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(errorWidget);
    
    errorTable = new QTableWidget();
    errorTable->setColumnCount(4);
    errorTable->setHorizontalHeaderLabels({"Dòng #", "Cột", "Lỗi", "Dữ liệu"});
    
    populateErrorTable();
    
    errorTable->resizeColumnsToContents();
    errorTable->horizontalHeader()->setStretchLastSection(true);
    
    layout->addWidget(errorTable);
    errorWidget->setLayout(layout);
    
    tabs->addTab(errorWidget, QString("Lỗi (%1)").arg(m_errorRowCount));
}

void ma_nganh_import_dialog::populateValidTable()
{
    int validRowIndex = 0;
    
    for (int i = 0; i < m_validatedRows.length(); ++i){
        if (m_validatedRows[i].isValid){
            const auto &rowData = m_validatedRows[i].data;
            
            validTable->insertRow(validRowIndex);
            for (int col = 0; col < 5 && col < rowData.length(); col++){
                validTable->setItem(validRowIndex, col, new QTableWidgetItem(rowData[col]));
            }
            validRowIndex++;
        }
    }
}

void ma_nganh_import_dialog::populateErrorTable()
{
    int errorRowIndex = 0;
    
    for (int i = 0; i < m_validatedRows.length(); ++i){
        const auto &row = m_validatedRows[i];
        if (!row.isValid){
            for (const auto &error : row.errors){
                errorTable->insertRow(errorRowIndex);
                
                errorTable->setItem(errorRowIndex, 0, new QTableWidgetItem(QString::number(error.rowNumber)));
                errorTable->setItem(errorRowIndex, 1, new QTableWidgetItem(error.columnName));
                errorTable->setItem(errorRowIndex, 2, new QTableWidgetItem(error.errorMessage));
                
                QString rowData = row.data.join(" | ");
                errorTable->setItem(errorRowIndex, 3, new QTableWidgetItem(rowData));
                
                // Highlight error rows
                for (int col = 0; col < 4; col++){
                    auto item = errorTable->item(errorRowIndex, col);
                    if (item){
                        item->setBackground(QColor(200, 50, 50)); // Dark red
                    }
                }
                
                errorRowIndex++;
            }
        }
    }
}
