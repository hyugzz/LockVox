QT +=   quick xml  network sql testlib
CONFIG += c++11 console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        Client/channellist.cpp \
        Client/channelmodel.cpp \
        Client/clientlist.cpp \
        Client/clientmodel.cpp \
        Client/cpacket.cpp \
        Client/cserver.cpp \
        Client/messagemodel.cpp \
        Client/uiworker.cpp \
        Client/main.cpp \
        Client/messagelist.cpp \
        Client/caudio.cpp \
        imageprovider.cpp \
        src/AbstractServer.cpp \
        src/cchannel.cpp \
        src/cclient.cpp  \
        src/cmessage.cpp \
        src/crole.cpp


HEADERS += \
        Client/includes/cpacket.h \
        Client/includes/channellist.h \
        Client/includes/channelmodel.h \
        Client/includes/clientlist.h \
        Client/includes/clientmodel.h \
        Client/includes/cserver.h \
        Client/includes/uiworker.h \
        Client/includes/config.h \
        Client/includes/messagelist.h \
        Client/includes/messagemodel.h \
        Client/includes/caudio.h \
        imageprovider.h \
        src/includes/AbstractServer.h \
        src/includes/cchannel.h \
        src/includes/cclient.h  \
        src/includes/cmessage.h \
        src/includes/crole.h \

INCLUDEPATH += \
        src/includes \
        Client/includes \
        Client/qml

DEPENDPATH += \
        src/includes \
        Client/includes \




#QML File ressources
RESOURCES += Client/qml.qrc
RESOURCES += $$files(Client/qml/*)


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = Client/qml/imports

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#DISTFILES += \
#    qml/ConnectServer.qml


win32: LIBS += -L$$PWD/libs/libmariadb/win32/ -llibmariadb
else: unix: LIBS += -L$$PWD/libs/libmariadb/unix/ -lmariadb
INCLUDEPATH += $$PWD/libs/libmariadb/include \
    $$PWD/libs/libmariadb/win32
DEPENDPATH += $$PWD/libs/libmariadb/win32

DISTFILES += \
    Client/qml/CustomQpushButton2.ui.qml \
    MenuBar.qml



