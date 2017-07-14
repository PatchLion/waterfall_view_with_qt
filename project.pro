TEMPLATE = app
CONFIG += console
TARGET = waterfall

QT += core gui widgets

CONFIG += c++11

include(public.pri)

INCLUDEPATH += .

HEADERS += *.h
SOURCES +=*.cpp




