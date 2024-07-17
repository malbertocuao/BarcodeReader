QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    mac_helpers.mm \
    main.cpp \
    barcodereader.cpp

HEADERS += \
    barcodereader.h

FORMS += \
    barcodereader.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

# Añadir las bibliotecas X11 para Linux
unix:!macx {
    LIBS += -lX11
}

# Incluir el framework Cocoa en macOS
macx {
    LIBS += -framework Cocoa
}
