#-------------------------------------------------
#
# Project created by QtCreator 2014-04-28T15:04:32
#
#-------------------------------------------------

QT       -= gui
QT       += core

TARGET = PonyQtSmtp
TEMPLATE = lib

DEFINES += PONYQTSMTP_LIBRARY

SOURCES += \
	src/PonyQtSmtp.cpp \
    src/PonyQtMessage.cpp

HEADERS += \
	src/PonyQtSmtp.h \
	src/ponyqtsmtp_global.h \
    src/PonyQtMessage.h \
    src/IPonyQtMessage.h

unix {
	target.path = /usr/lib
	INSTALLS += target
}

OTHER_FILES += \
	LICENSE
