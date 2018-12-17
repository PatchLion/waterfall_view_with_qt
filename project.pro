TEMPLATE = app
CONFIG += console
TARGET = waterfall

QT += core gui widgets network

CONFIG += c++11

include(public.pri)

INCLUDEPATH += . ImageLib/includes

HEADERS += \
    ImageItem.h \
    ImageSreachThread.h \
    WaterFallItem.h \
    WaterFallScrollArea.h \
    WaterFallWidget.h \
    ImageLib/includes/ImageMacros.h \
    ImageLib/includes/ImageReader.h \
    ImageLib/includes/ImageReadQueue.h \
    ImageLib/includes/ImageReadThread.h \
    ImageLib/includes/ImageStructs.h \
    ImageLib/includes/ImageWriter.h \
    ImageLib/includes/ImageWriteThread.h

SOURCES += \
    ImageItem.cpp \
    ImageSreachThread.cpp \
    main.cpp \
    WaterFallItem.cpp \
    WaterFallScrollArea.cpp \
    WaterFallWidget.cpp \
    ImageLib/sources/ImageReader.cpp \
    ImageLib/sources/ImageReadQueue.cpp \
    ImageLib/sources/ImageReadThread.cpp \
    ImageLib/sources/ImageWriter.cpp \
    ImageLib/sources/ImageWriteThread.cpp





