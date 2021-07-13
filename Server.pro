QT       += core gui multimedia xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network sql

CONFIG += c++11 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Server/caudio.cpp \
    Server/cookiesmanager.cpp \
    src/AbstractServer.cpp \
    src/abstractaudio.cpp \
    src/cchannel.cpp \
    src/cclient.cpp \
    src/cdatabase.cpp \
    src/cmessage.cpp \
    src/cpacket.cpp \
    Server/cserver.cpp \
    Server/main.cpp \
    src/crole.cpp \
    Server/sha256.cpp \
    Client/messagelist.cpp \
    src/csessioncookie.cpp

HEADERS += \
    src/includes/AbstractServer.h \
    Server/includes/caudio.h \
    Server/includes/cookiesmanager.h \
    Server/includes/sha256.h \
    Server/includes/cserver.h \
    Server/config.h \
    Server/includes/csessioncookie.h \
    src/includes/cmessage.h \
    src/includes/cchannel.h \
    src/includes/cclient.h \
    Server/includes/cdatabase.h \
    Server/includes/cpacket.h \
    src/includes/cmessage.h \
    src/includes/crole.h \
    Client/includes/messagelist.h

FORMS +=


INCLUDEPATH += src \
    src/includes \
    Server/includes

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/libs/libmariadb/win32/ -llibmariadb
else: unix: LIBS += -L$$PWD/libs/libmariadb/unix -lmariadb
INCLUDEPATH += $$PWD/libs/libmariadb/include \
    $$PWD/libs/libmariadb/win32
DEPENDPATH += $$PWD/libs/libmariadb/win32
