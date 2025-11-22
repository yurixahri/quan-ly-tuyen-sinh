#ifndef STRING_H
#define STRING_H

#include <Qstring>
#include <QRegularExpression>

inline void trimLeadingAndTrailing(QString &string){
    static QRegularExpression regex("^\\s+|\\s+$");
    string = string.replace(regex, "");
}

#endif // STRING_H
