#include "db.h"

QSqlDatabase db;

qx::QxSqlDatabase *qx_db = qx::QxSqlDatabase::getSingleton();

bool beginDB(QSqlDatabase &db){
    db.setHostName(host_name);
    db.setDatabaseName(database_name);
    db.setUserName(username);
    db.setPassword(password);
    db.setPort(database_port);

    if (!db.open())
        return false;
    else
        return true;
}

bool beginQX_DB(qx::QxSqlDatabase *qx_db){
    qx_db->setDriverName("QPSQL");
    qx_db->setHostName(host_name);
    qx_db->setDatabaseName(database_name);
    qx_db->setUserName(username);
    qx_db->setPassword(password);
    qx_db->setPort(database_port);

    db = qx_db->getDatabase();
    db.open();

    if (!db.isOpen())
        return false;
    else
        return true;
}

