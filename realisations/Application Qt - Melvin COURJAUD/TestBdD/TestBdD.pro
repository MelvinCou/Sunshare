QT -= gui
QT += sql serialport

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/compteursdm.cpp \
        src/gestionnaire.cpp \
        src/linky.cpp \
        src/basededonnees.cpp \
        main.cpp

HEADERS += \
        include/compteursdm.h \
        include/gestionnaire.h \
        include/linky.h \
        include/basededonnees.h

INCLUDEPATH += /home/pi/pigpio-master/ include

LIBS += -lpigpio -lrt -lpthread

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
