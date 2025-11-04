QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Camera.cpp \
    Castelo.cpp \
    Curva.cpp \
    DisplayFile.cpp \
    Drawable.cpp \
    Linha.cpp \
    Matriz.cpp \
    ModeloOBJ.cpp \
    Polygon.cpp \
    Ponto.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Camera.h \
    Castelo.h \
    Curva.h \
    DisplayFile.h \
    Drawable.h \
    Linha.h \
    Matriz.h \
    ModeloOBJ.h \
    Polygon.h \
    Ponto.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
