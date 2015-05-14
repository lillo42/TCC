#-------------------------------------------------
#
# Project created by QtCreator 2015-04-09T13:09:49
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Aplicacao
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -L/usr/local/lib -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_ts -lopencv_video -lopencv_videostab

SOURCES += main.cpp \
    LBP/lbp.cpp \
    Base/classificadorbase.cpp \
    Adaboost/adaboost.cpp \
    RN/redeneural.cpp \

HEADERS += \
    LBP/lbp.h \
    Base/classificadorbase.h \
    Adaboost/adaboost.h \
    RN/redeneural.h \
