#ifndef STRING_H
#define STRING_H

#include <Qstring>
#include <QRegularExpression>

inline void trimLeadingAndTrailing(QString &string){
    static QRegularExpression regex("^\\s+|\\s+$");
    string = string.replace(regex, "");
}

inline void upperCaseFirstLetter(QString &string){
    string = string.toLower();
    string[0] = string[0].toUpper();
}

inline bool isPhoneNumberValid(QString &string){
    static QRegularExpression regex("^\\d{10,11}$");
    QRegularExpressionMatch match = regex.match(string);
    return match.hasMatch();
}

#endif // STRING_H
