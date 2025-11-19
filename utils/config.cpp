#include "config.h"

QString host_name;
QString database_name;
uint16_t database_port;
QString username;
QString password;

QSettings *settings = new QSettings("config.ini", QSettings::IniFormat);

void getConfig() {
    host_name = settings->value("database/host").toString();
    database_name = settings->value("database/db").toString();
    username = settings->value("database/username").toString();
    password = settings->value("database/password").toString();
    database_port = settings->value("database/port").toUInt();
}
