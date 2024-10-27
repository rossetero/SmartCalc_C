QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    $$files(../core/math_calc/*.c) \
    $$files(../core/fin_calc/*.c) \
    qcustomplot.cpp \
    plotwindow.cpp


HEADERS += \
    mainwindow.h \
    ../core/core.h \
    $$files(../core/math_calc/*.h) \
    $$files(../core/fin_calc/*.h) \
     qcustomplot.h \
    plotwindow.h

FORMS += \
    mainwindow.ui \
    plotwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
