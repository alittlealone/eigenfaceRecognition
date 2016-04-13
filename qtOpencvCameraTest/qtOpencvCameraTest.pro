#-------------------------------------------------
#
# Project created by QtCreator 2016-04-11T22:49:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtOpencvCameraTest
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp

HEADERS  += dialog.h

FORMS    += dialog.ui

INCLUDEPATH += D:\opencv\opencv\build\include\opencv
INCLUDEPATH += D:\opencv\opencv\build\include\opencv2
INCLUDEPATH += D:\opencv\opencv\build\include

CONFIG(debug, debug | release) {
#debug libs
LIBS += -L"D:\opencv\opencv\build\x86\vc12\lib" \
-lopencv_calib3d2410d \
-lopencv_contrib2410d \
-lopencv_core2410d \
-lopencv_features2d2410d \
-lopencv_flann2410d \
-lopencv_gpu2410d \
-lopencv_highgui2410d \
-lopencv_imgproc2410d \
-lopencv_legacy2410d \
-lopencv_ml2410d \
-lopencv_nonfree2410d \
-lopencv_objdetect2410d \
-lopencv_ocl2410d \
-lopencv_photo2410d \
-lopencv_stitching2410d \
-lopencv_superres2410d \
-lopencv_ts2410d \
-lopencv_video2410d \
-lopencv_videostab2410d
}
