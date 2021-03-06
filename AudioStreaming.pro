QT += quick
QT += network
QT += multimedia
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        appmanager.cpp \
        audioplayer.cpp \
        auth.cpp \
        main.cpp \
        mysongs.cpp \
        mysongsmodel.cpp \
        networkmanager.cpp

RESOURCES += qml.qrc

TRANSLATIONS += \
    AudioStreaming_en_150.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    appmanager.h \
    audioplayer.h \
    auth.h \
    mysongs.h \
    mysongsmodel.h \
    networkmanager.h

DISTFILES += \
    app_activity_indicator.js
