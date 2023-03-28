QT -= gui
QT += sql websockets

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        db/dbserver.cpp \
        db/po/groupmsgpo.cpp \
        db/po/privatemsgpo.cpp \
        db/po/userpo.cpp \
        main.cpp \
        tools/db/dbhelper.cpp \
        tools/dispatcher/dispatcherservice.cpp \
        tools/dispatcher/messageanaly.cpp \
        tools/json/jsonhelper.cpp \
        tools/manager/socketmanager.cpp \
        tools/yaml/yamlanalyse.cpp \
        user/userservice.cpp \
        user/usersession.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




HEADERS += \
    db/dbserver.h \
    db/po/groupmsgpo.h \
    db/po/privatemsgpo.h \
    db/po/userpo.h \
    tools/db/dbhelper.h \
    tools/dispatcher/dispatcherservice.h \
    tools/dispatcher/messageanaly.h \
    tools/enum/MessageTypeEnum.h \
    tools/enum/ResultEnum.h \
    tools/json/jsonhelper.h \
    tools/manager/socketmanager.h \
    tools/yaml/yamlanalyse.h \
    user/userservice.h \
    user/usersession.h

RESOURCES += \
    config.qrc



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/tools/hiredis-master/build/Release -lhiredis
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/tools/hiredis-master/build/Release -lhiredis
else:unix:!macx: LIBS += -L$$PWD/tools/hiredis-master/build/ -lhiredis

INCLUDEPATH += $$PWD/tools/hiredis-master/build/Release
DEPENDPATH += $$PWD/tools/hiredis-master/build/Release

