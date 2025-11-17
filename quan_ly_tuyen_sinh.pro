QT       += core gui sql core5compat

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
INCLUDEPATH += C:/msys64/mingw64/include
LIBS += -LC:/msys64/mingw64/lib -lQxOrm -lpq

# QXlsx code for Application Qt project
QXLSX_PARENTPATH=./QXlsx/         # current QXlsx path is . (. means curret directory)
QXLSX_HEADERPATH=./QXlsx/header/  # current QXlsx header path is ./header/
QXLSX_SOURCEPATH=./QXlsx/source/  # current QXlsx source path is ./source/
include(./QXlsx/QXlsx.pri)

include(./QxOrm/QxOrm.pri)

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    db/db.cpp \
    db/models/mon_hoc.cpp \
    db/models/to_hop_mon.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    utils/config.cpp

HEADERS += \
    db/db.h \
    db/models/mon_hoc.h \
    db/models/to_hop_mon.h \
    db/monhoc_dao.h \
    excel/read_excel.h \
    logindialog.h \
    mainwindow.h \
    pages/monhoc_page.h \
    utils/config.h

FORMS += \
    logindialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc
