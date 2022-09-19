TEMPLATE = app
TARGET = QML-Calculator

QT += core widgets quick qml
CONFIG -= flat

#Release:DESTDIR = ../Compiles/QML-Calculator/Release
#Debug:DESTDIR = ../Compiles/QML-Calculator/Debug
#
#Release:OBJECTS_DIR = ./Build/Release
#Release:MOC_DIR = ./Build/Release/moc
#Release:UI_DIR = ./Build/Release/ui
#Release:RCC_DIR = ./Build/Release/rcc
#
#Debug:OBJECTS_DIR = ./Build/Debug
#Debug:MOC_DIR = ./Build/Debug/moc
#Debug:UI_DIR = ./Build/Debug/ui
#Debug:RCC_DIR = ./Build/Debug/rcc

BACK = $$PWD/src/back
FRONT = $$PWD/src/front

HEADERS += $$BACK/Calculator.h \
    $$BACK/OperationHistory.h \
    $$BACK/ConverterHandler.h \
    $$BACK/Converter.h \
    $$BACK/Utils.h


SOURCES += $$BACK/Calculator.cpp \
    $$BACK/ConverterHandler.cpp \
    $$BACK/Converter.cpp \
    $$BACK/OperationHistory.cpp \
    $$BACK/main.cpp

RESOURCES += $$FRONT/qml.qrc
