# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/MinGW_1-Windows
TARGET = Guitar_learning
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
QT = core gui
SOURCES += main.cpp Tuner.cpp Bar.cpp kiss_fft/kiss_fftndr.c Carriage.cpp kiss_fft/kiss_fftr.c kiss_fft/kiss_fft.c Scholar.cpp Note.cpp kiss_fft/kfc.c SingleNote.cpp Track.cpp Chord.cpp AudioIO.cpp kiss_fft/kiss_fftnd.c Lesson.cpp SingleToneAnalyzer.cpp
HEADERS += SingleNote.h Chord.h Track.h Tuner.h Analyzer.h AudioIO.h kiss_fft/kiss_fftr.h Scholar.h kiss_fft/kiss_fftnd.h Note.h kiss_fft/kfc.h Lesson.h kiss_fft/_kiss_fft_guts.h Carriage.h kiss_fft/kiss_fft.h Bar.h kiss_fft/kiss_fftndr.h SingleToneAnalyzer.h
FORMS += Scholar.ui Tuner.ui
RESOURCES += Images.qrc
TRANSLATIONS +=
OBJECTS_DIR = build/Release/MinGW_1-Windows
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc.exe
QMAKE_CXX = g++.exe
DEFINES += 
INCLUDEPATH += 
LIBS += 
