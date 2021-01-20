QT       += core gui multimedia xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network sql

CONFIG += c++11 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0




SOURCES += \
    Client/changeusernamewindow.cpp \
    Client/channelwidget.cpp \
    Client/loginwindow.cpp \
    Client/registerwindow.cpp \
    Client/userstatuswindow.cpp \
    src/AbstractServer.cpp \
    src/audioinput.cpp \
    src/audiooutput.cpp \
    src/cchannel.cpp \
    src/cclient.cpp \
    src/cpacket.cpp \
    Client/cserver.cpp \
    Client/main.cpp \
    Client/mainwindow.cpp \
    src/cmessage.cpp \
    src/AbstractServer.cpp

HEADERS += \
    Client/changeusernamewindow.h \
    Client/channelwidget.h \
    Client/cserver.h \
    Client/loginwindow.h \
    Client/mainwindow.h \
    Client/registerwindow.h \
    Client/userstatuswindow.h \
    src/includes/AbstractServer.h \
    src/includes/audioinput.h \
    src/includes/audiooutput.h \
    src/includes/cchannel.h \
    src/includes/cclient.h \
    src/includes/cpacket.h \
    src/includes/AbstractServer.h \
    src/includes/cmessage.h \
    Client/cserver.h


FORMS += \
    Client/ChangeUsername.ui \
    Client/ChannelList.ui \
    Client/Message.ui \
    Client/UserInfos.ui \
    Client/UserStatus.ui \
    Client/changeusernamewindow.ui \
    Client/channelwidget.ui \
    Client/loginwindow.ui \
    Client/mainwindow.ui \
    Client/registerwindow.ui \
    Client/testMain.ui \
    Client/untitled.ui \
    Client/userstatuswindow.ui


INCLUDEPATH += src \
    src/include \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



