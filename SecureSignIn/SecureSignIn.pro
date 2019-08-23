#-------------------------------------------------
#
# Project created by QtCreator 2018-07-30T03:23:02
#
#-------------------------------------------------

#QMAKE_CXXFLAGS += -lX11

# add lX11 compile flag only if building on Linux
linux-g++ | linux-g++-64 | linux-g++-32 {
LIBS += -lX11
}

QT       += core gui widgets

TARGET = SecureSignIn
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
	main.cpp \
    secure_sign_in_window.cpp \
    output_window.cpp \
    secure_sign_in.cpp \
    tty.cpp \
    x11_clipboard.cpp \
    workerthread.cpp

HEADERS += \
    secure_sign_in_window.hpp \
    output_window.hpp \
    secure_sign_in.hpp \
    tty.hpp \
    x11_clipboard.hpp \
    workerthread.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    Resources/StyleSheets/gitkraken_cryogen.qss \
    cryogen.mac.qss
