#ifndef DB_H
#define DB_H

#include <QSqlDatabase>
#include <QxOrm.h>
#include <QxDao/QxSqlDatabase.h>
#include "utils/config.h"

extern QSqlDatabase db;
extern qx::QxSqlDatabase *qx_db;

bool beginDB(QSqlDatabase &db);
bool beginQX_DB(qx::QxSqlDatabase *qx_db);

#endif // DB_H
