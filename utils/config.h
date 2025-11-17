#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>

extern QString host_name;
extern QString database_name;
extern uint16_t database_port;
extern QString username;
extern QString password;

void setConfig(QSettings *settings);

#endif // CONFIG_H
