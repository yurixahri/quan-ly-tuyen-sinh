#ifndef MA_NGANH_IMPORT_DIALOG_H
#define MA_NGANH_IMPORT_DIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStringList>
#include <QList>
#include <QTabWidget>
#include <optional>
#include "ma_nganh_import_validator.h"

class ma_nganh_import_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit ma_nganh_import_dialog(std::optional<QList<QStringList>> data, QWidget *parent = nullptr);
    ~ma_nganh_import_dialog();
    
    bool hasValidData() const { return m_validRowCount > 0; }
    int getValidRowCount() const { return m_validRowCount; }
    int getErrorRowCount() const { return m_errorRowCount; }

private:
    void setupUI();
    void validateAndDisplayData(const QList<QStringList> &data);
    void createValidDataTab(QTabWidget *tabs);
    void createErrorDataTab(QTabWidget *tabs);
    void populateValidTable();
    void populateErrorTable();
    
    QList<QStringList> m_rawData;
    QVector<ValidatedRow> m_validatedRows;
    QList<QStringList> m_preprocessedData;
    int m_validRowCount = 0;
    int m_errorRowCount = 0;
    
    QTableWidget *validTable;
    QTableWidget *errorTable;
    QLabel *summaryLabel;
    QPushButton *importBtn;
    QPushButton *cancelBtn;
};

#endif // MA_NGANH_IMPORT_DIALOG_H
