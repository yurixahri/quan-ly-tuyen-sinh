QT += core gui sql core5compat

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
    db/models/nhom_nganh.cpp \
    db/models/ptxt.cpp \
    db/models/to_hop_mon.cpp \
    db/models/nganh.cpp \
    db/models/ma_nganh_ptxt.cpp \
    db/models/ma_nganh_tohop.cpp \
    db/models/ma_nganh.cpp \
    db/models/thi_sinh.cpp \
    db/models/chungchi_tienganh.cpp \
    db/models/diem_hocba.cpp \
    db/models/diem_thi_sat.cpp \
    db/models/doat_giai.cpp \
    db/models/ma_chungchinn.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    ui/add_mon_hoc_dialog.cpp \
    ui/change_mon_hoc_dialog.cpp \
    ui/components/MultiSelectComboBox.cpp \
    ui/custom_message_box.cpp \
    ui/ma_nganh/ma_nganh_dialog.cpp \
    ui/nganh/nganh_dialog.cpp \
    ui/nhom_nganh/nhom_nganh_dialog.cpp \
    ui/ptxt/ptxt_dialog.cpp \
    ui/thi_sinh/chungchi_tienganh_dialog.cpp \
    ui/thi_sinh/diem_hocba_dialog.cpp \
    ui/thi_sinh/diem_sat_dialog.cpp \
    ui/thi_sinh/doat_giai_dialog.cpp \
    ui/thi_sinh/thi_sinh_detail.cpp \
    ui/thi_sinh/thi_sinh_dialog.cpp \
    ui/tohop/add_tohop_dialog.cpp \
    utils/config.cpp

HEADERS += \
    db/db.h \
    db/models/mon_hoc.h \
    db/models/nhom_nganh.h \
    db/models/ptxt.h \
    db/models/to_hop_mon.h \
    db/models/nganh.h \
    db/models/ma_nganh_tohop.h \
    db/models/ma_nganh_ptxt.h \
    db/models/ma_nganh.h \
    db/models/thi_sinh.h \
    db/models/chungchi_tienganh.h \
    db/models/diem_hocba.h \
    db/models/diem_thi_sat.h \
    db/models/doat_giai.h \
    db/models/ma_chungchinn.h \
    db/monhoc_dao.h \
    db/nganh_dao.h \
    db/nhom_nganh_dao.h \
    db/ptxt_dao.h \
    db/thi_sinh_dao.h \
    db/tohop_dao.h \
    db/ma_nganh_dao.h \
    db/diem_hocba_dao.h \
    db/diem_thi_sat_dao.h \
    db/doat_giai_dao.h \
    db/ma_chungchinn_dao.h \
    db/chungchi_tienganh_dao.h \
    excel/read_excel.h \
    logindialog.h \
    mainwindow.h \
    pages/ma_nganh_page.h \
    pages/monhoc_page.h \
    pages/nganh_page.h \
    pages/nhom_nganh_page.h \
    pages/ptxt_page.h \
    pages/thi_sinh_page.h \
    pages/tohop_page.h \
    ui/add_mon_hoc_dialog.h \
    ui/change_mon_hoc_dialog.h \
    ui/components/MultiSelectComboBox.h \
    ui/custom_message_box.h \
    ui/ma_nganh/ma_nganh_dialog.h \
    ui/nganh/nganh_dialog.h \
    ui/nhom_nganh/nhom_nganh_dialog.h \
    ui/ptxt/ptxt_dialog.h \
    ui/thi_sinh/chungchi_tienganh_dialog.h \
    ui/thi_sinh/diem_hocba_dialog.h \
    ui/thi_sinh/diem_sat_dialog.h \
    ui/thi_sinh/doat_giai_dialog.h \
    ui/thi_sinh/thi_sinh_detail.h \
    ui/thi_sinh/thi_sinh_dialog.h \
    ui/tohop/add_tohop_dialog.h \
    utils/config.h \
    utils/fs.h \
    utils/string.h

FORMS += \
    logindialog.ui \
    mainwindow.ui \
    ui/add_mon_hoc_dialog.ui \
    ui/change_mon_hoc_dialog.ui \
    ui/custom_message_box.ui \
    ui/ma_nganh/ma_nganh_dialog.ui \
    ui/nganh/nganh_dialog.ui \
    ui/nhom_nganh/nhom_nganh_dialog.ui \
    ui/ptxt/ptxt_dialog.ui \
    ui/thi_sinh/chungchi_tienganh_dialog.ui \
    ui/thi_sinh/diem_hocba_dialog.ui \
    ui/thi_sinh/diem_sat_dialog.ui \
    ui/thi_sinh/doat_giai_dialog.ui \
    ui/thi_sinh/thi_sinh_detail.ui \
    ui/thi_sinh/thi_sinh_dialog.ui \
    ui/tohop/add_tohop_dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc

DISTFILES += \
    assets/images/delete-128.png \
    assets/images/error-96.png \
    assets/images/info-96.png \
    assets/images/question-96.png \
    assets/images/warning-96.png
