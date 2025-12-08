#ifndef READ_EXCEL_H
#define READ_EXCEL_H

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;


inline std::optional<QList<QStringList>> readExcel(QString &file_path){
    Document xlsx(file_path);
    if (!xlsx.load()) {
        qDebug() << "File not found or failed to load.";
        return std::nullopt;
    }
    QStringList sheets = xlsx.sheetNames();
    xlsx.selectSheet(sheets.at(0));

    auto dim = xlsx.dimension();
    int firstRow = dim.firstRow()+2;
    int lastRow  = dim.lastRow();
    int firstCol = dim.firstColumn()+1;
    int lastCol  = dim.lastColumn();

    QList<QStringList> rows;

    for (int row = firstRow; row <= lastRow; ++row) {
        QStringList rowData;

        for (int col = firstCol; col <= lastCol; ++col) {
            auto cell = xlsx.cellAt(row, col);
            rowData << (cell ? cell->value().toString() : "");
        }
        //qDebug() << "Row" << row << ":" << rowData;
        rows << rowData;
    }

    return rows;
}


#endif // READ_EXCEL_H
