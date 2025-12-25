#include "ma_nganh_import_validator.h"
#include "db/nganh_dao.h"
#include "db/nhom_nganh_dao.h"
#include <QDebug>

const QStringList MaNganhImportValidator::EXPECTED_HEADERS = {"MÃ NGÀNH", "NGÀNH", "NHÓM NGÀNH", "TỔ HỢP"};

MaNganhImportValidator::MaNganhImportValidator()
{
}

std::optional<QList<QStringList>> MaNganhImportValidator::extractDataWithHeaderValidation(const QList<QStringList> &rawData, QString &errorMessage)
{
    qDebug() << "=== Starting Data Extraction with Header Validation ===";
    qDebug() << "Total rows read:" << rawData.length();
    
    // Note: readExcel() already skips the first 2 rows (title + header)
    // So rawData index 0 is the first data row, not a header
    
    if (rawData.length() < 1){
        errorMessage = "File Excel không chứa dữ liệu";
        qDebug() << "ERROR:" << errorMessage;
        return std::nullopt;
    }
    
    qDebug() << "Data rows: " << rawData.length();
    for (int i = 0; i < qMin(3, rawData.length()); ++i){
        qDebug() << "Row" << i << ":" << rawData[i];
    }
    
    // Validate first data row has correct number of columns
    // Note: readExcel() skips the STT column, so we expect 4 columns
    if (rawData[0].length() != 4){
        errorMessage = QString("Format excel không hợp lệ. Cần 4 cột nhưng nhận %1 cột").arg(rawData[0].length());
        qDebug() << "ERROR:" << errorMessage;
        return std::nullopt;
    }
    
    qDebug() << "✓ Data extraction successful - " << rawData.length() << " rows ready for validation";
    return rawData;
}

bool MaNganhImportValidator::validateHeaders(const QStringList &headers)
{
    if (headers.length() != EXPECTED_HEADERS.length()){
        return false;
    }
    
    for (int i = 0; i < EXPECTED_HEADERS.length(); ++i){
        if (headers[i].trimmed() != EXPECTED_HEADERS[i]){
            return false;
        }
    }
    
    return true;
}

QList<QStringList> MaNganhImportValidator::preprocessData(const QList<QStringList> &rawData)
{
    QList<QStringList> cleanedData;
    
    for (const auto &row : rawData){
        // Trim all fields
        QStringList trimmedRow;
        bool isEmptyRow = true;
        
        for (const auto &cell : row){
            QString trimmed = cell.trimmed();
            trimmedRow.append(trimmed);
            if (!trimmed.isEmpty()){
                isEmptyRow = false;
            }
        }
        
        // Skip empty rows
        if (!isEmptyRow){
            cleanedData.append(trimmedRow);
        }
    }
    
    return cleanedData;
}

QVector<ValidatedRow> MaNganhImportValidator::validateRows(const QList<QStringList> &data)
{
    QVector<ValidatedRow> validatedRows;
    
    for (int rowNum = 0; rowNum < data.length(); ++rowNum){
        ValidatedRow validRow;
        validRow.data = data[rowNum];
        validRow.isValid = true;
        
        const auto &row = data[rowNum];
        
        // Validate column count (4 columns: MÃ NGÀNH, NGÀNH, NHÓM NGÀNH, TỔ HỢP)
        // Note: readExcel() skips the STT column
        if (row.length() != 4){
            validRow.isValid = false;
            validRow.errors.append(ValidationError{
                rowNum + 1,
                "General",
                QString("Số cột không hợp lệ. Cần 4 cột, nhưng nhận %1 cột").arg(row.length())
            });
            validatedRows.append(validRow);
            continue;
        }
        
        // Column 0: MÃ NGÀNH (Mandatory)
        if (isMandatoryFieldEmpty(row[0])){
            validRow.isValid = false;
            validRow.errors.append(ValidationError{rowNum + 1, "MÃ NGÀNH", "Trường mã ngành không được để trống"});
        }
        
        // Column 1: NGÀNH (Mandatory)
        if (isMandatoryFieldEmpty(row[1])){
            validRow.isValid = false;
            validRow.errors.append(ValidationError{rowNum + 1, "NGÀNH", "Trường ngành không được để trống"});
        }
        
        // Column 2: NHÓM NGÀNH (Mandatory)
        if (isMandatoryFieldEmpty(row[2])){
            validRow.isValid = false;
            validRow.errors.append(ValidationError{rowNum + 1, "NHÓM NGÀNH", "Trường nhóm ngành không được để trống"});
        }
        
        // Column 3: TỔ HỢP (Mandatory)
        if (isMandatoryFieldEmpty(row[3])){
            validRow.isValid = false;
            validRow.errors.append(ValidationError{rowNum + 1, "TỔ HỢP", "Trường tổ hợp không được để trống"});
        }
        
        validatedRows.append(validRow);
    }
    
    return validatedRows;
}

bool MaNganhImportValidator::isValidChiTieu(const QString &value)
{
    bool ok;
    int chiTieu = value.toInt(&ok);
    return ok && chiTieu >= 0;
}

bool MaNganhImportValidator::isMandatoryFieldEmpty(const QString &value)
{
    return value.trimmed().isEmpty();
}

QString MaNganhImportValidator::getNganhErrorMessage(const QString &nganhName)
{
    return QString("Ngành '%1' không tồn tại").arg(nganhName);
}
