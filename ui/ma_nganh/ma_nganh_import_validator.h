#ifndef MA_NGANH_IMPORT_VALIDATOR_H
#define MA_NGANH_IMPORT_VALIDATOR_H

#include <QString>
#include <QStringList>
#include <QList>
#include <QVector>
#include <optional>

struct ValidationError {
    int rowNumber;
    QString columnName;
    QString errorMessage;
};

struct ValidatedRow {
    QStringList data;
    bool isValid;
    QVector<ValidationError> errors;
};

class MaNganhImportValidator
{
public:
    MaNganhImportValidator();
    
    // Step 0: Extract and validate header
    static std::optional<QList<QStringList>> extractDataWithHeaderValidation(const QList<QStringList> &rawData, QString &errorMessage);
    
    // Step 1: Validate structural integrity
    static bool validateHeaders(const QStringList &headers);
    
    // Step 2: Pre-processing (trim and remove empty rows)
    static QList<QStringList> preprocessData(const QList<QStringList> &rawData);
    
    // Step 3: Validate each row with business logic
    static QVector<ValidatedRow> validateRows(const QList<QStringList> &data);
    
    // Helper functions
    static bool isValidChiTieu(const QString &value);
    static bool isMandatoryFieldEmpty(const QString &value);
    static QString getNganhErrorMessage(const QString &nganhName);
    
private:
    static const QStringList EXPECTED_HEADERS;
};

#endif // MA_NGANH_IMPORT_VALIDATOR_H
