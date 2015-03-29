#-------------------------------------------------
#
# Project created by QtCreator 2015-03-29T19:00:50
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
    Adaboost/adaboost.cpp \
    RedeNeural/redeneural.cpp \
    Base/lbpbase.cpp \
    Outros/leitor.cpp \
    Outros/lbp.cpp \
    Base/classificadorbase.cpp \
    Adaboost/lbpadaboost.cpp \
    RedeNeural/lbpredeneural.cpp

HEADERS += \
    Adaboost/adaboost.h \
    RedeNeural/redeneural.h \
    Base/lbpbase.h \
    Outros/leitor.h \
    Outros/lbp.h \
    Base/classificadorbase.h \
    Adaboost/lbpadaboost.h \
    RedeNeural/lbpredeneural.h
