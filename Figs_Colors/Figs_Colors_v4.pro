#-------------------------------------------------
#
# Project created by QtCreator 2016-06-07T21:54:08
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Figs_Colors_v4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    canswers.cpp \
    cchild_info.cpp \
    cclient.cpp \
    ccolor.cpp \
    cfigure.cpp \
    cperformance.cpp \
    csession.cpp \
    qcustomplot.cpp \
    cposcenter.cpp

HEADERS  += mainwindow.h \
    cactivitytype.h \
    canswers.h \
    cchild_info.h \
    cclient.h \
    ccolor.h \
    ccolorstype.h \
    cfigstype.h \
    cfigure.h \
    cperformance.h \
    csession.h \
    qcustomplot.h \
    cposcenter.h

FORMS    += mainwindow.ui

INCLUDEPATH += C:\\OpenCV-3.0.0\opencv\build\include

LIBS += -LC:\\OpenCV-3.0.0\\mybuild\\lib\\Debug \
       -lopencv_calib3d300d \
       -lopencv_core300d \
       -lopencv_features2d300d \
       -lopencv_flann300d \
       -lopencv_hal300d \
       -lopencv_highgui300d \
       -lopencv_imgcodecs300d \
       -lopencv_imgproc300d \
       -lopencv_ml300d \
       -lopencv_objdetect300d \
       -lopencv_photo300d \
       -lopencv_shape300d \
       -lopencv_stitching300d \
       -lopencv_superres300d \
       -lopencv_ts300d \
       -lopencv_video300d \
       -lopencv_videoio300d \
       -lopencv_videostab300d
