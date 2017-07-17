TEMPLATE = app
CONFIG += console
TARGET = waterfall

QT += core gui widgets network

CONFIG += c++11

include(public.pri)

INCLUDEPATH += . ImageLib/includes

HEADERS += *.h ImageLib/includes/*.h
SOURCES +=*.cpp ImageLib/sources/*.cpp




