TEMPLATE = app
CONFIG += console
TARGET = waterfall

QT += core gui widgets network

CONFIG += c++11

include(public.pri)
INCLUDEPATH += . ImageLib/includes

LIBS += -LImageLib/$(Platform)/$(Configuration) -lImageLib
HEADERS += *.h
SOURCES +=*.cpp




