TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

LIBS += "-L/usr/lib/x86_86-gnu-linux"

LIBS += -lopencv_highgui -lopencv_core  -lopencv_imgproc  -lopencv_calib3d  -lopencv_features2d  -lopencv_video



