#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include <QSharedMemory>
#include "utils/config.h"
#include "ui/custom_message_box.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    getConfig();

    QSharedMemory sharedMemory;
    sharedMemory.setKey("quanlysv");
    if (!sharedMemory.create(1)) {
        custom_message_box("", "Tiến trình đã tồn tại", custom_message_box::Warning).exec();
        return 0;
    }

    loginDialog login;

    if (login.exec() == QDialog::Accepted) {
        MainWindow w;
        w.show();        
        return a.exec();
    }
    return 0;
}
