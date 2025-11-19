#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include "utils/config.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    getConfig();

    loginDialog login;

    if (login.exec() == QDialog::Accepted) {
        MainWindow w;
        w.show();        
        return a.exec();
    }
    return 0;
}
