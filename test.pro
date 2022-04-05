#-------------------------------------------------
#
# Project created by QtCreator 2017-08-27T11:21:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test_cv
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

LIBS += -LD:\opencv_build\install\x64\vc17\lib -lopencv_core455d -lopencv_imgproc455d -lopencv_highgui455d -lopencv_imgcodecs455d -lopencv_videoio455d -lopencv_video455d -lopencv_calib3d455d -lopencv_photo455d -lopencv_features2d455d
INCLUDEPATH += D:\opencv_build\install\include
DEPENDPATH += D:\opencv_build\install\include
