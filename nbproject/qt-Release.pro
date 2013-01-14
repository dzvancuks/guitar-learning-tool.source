# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/MinGW_1-Windows
TARGET = Guitar_learning
VERSION = 0.2
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
QT = core gui
SOURCES += "E:/My Documents/NetBeansProjects/Guitar_learning/Effect.cpp" "E:/My Documents/NetBeansProjects/Guitar_learning/ChordAnalyzer.cpp" main.cpp Tuner.cpp Bar.cpp kiss_fft/kiss_fftndr.c "E:/My Documents/NetBeansProjects/Guitar_learning/Mixer.cpp" Carriage.cpp "E:/My Documents/NetBeansProjects/Guitar_learning/EffectEcho.cpp" kiss_fft/kiss_fftr.c kiss_fft/kiss_fft.c "E:/My Documents/NetBeansProjects/Guitar_learning/Metronome.cpp" Scholar.cpp "E:/My Documents/NetBeansProjects/Guitar_learning/EffectPump.cpp" "E:/My Documents/NetBeansProjects/Guitar_learning/EffectDistortion.cpp" Tutor.cpp Note.cpp kiss_fft/kfc.c "E:/My Documents/NetBeansProjects/Guitar_learning/LessonFile.pb.cc" SingleNote.cpp LoadStore.cpp Track.cpp Chord.cpp AudioIO.cpp kiss_fft/kiss_fftnd.c SingleToneAnalyzer.cpp Lesson.cpp
HEADERS += Tutor.h SingleNote.h Chord.h Track.h Tuner.h AudioIO.h kiss_fft/kiss_fftr.h LoadStore.h Scholar.h Note.h kiss_fft/kiss_fftnd.h "E:/My Documents/NetBeansProjects/Guitar_learning/EffectDistortion.h" "E:/My Documents/NetBeansProjects/Guitar_learning/EffectPump.h" "E:/My Documents/NetBeansProjects/Guitar_learning/EffectEcho.h" kiss_fft/_kiss_fft_guts.h "E:/My Documents/NetBeansProjects/Guitar_learning/Effect.h" kiss_fft/kfc.h Lesson.h Carriage.h "E:/My Documents/NetBeansProjects/Guitar_learning/ChordAnalyzer.h" kiss_fft/kiss_fft.h "E:/My Documents/NetBeansProjects/Guitar_learning/Mixer.h" Bar.h kiss_fft/kiss_fftndr.h SingleToneAnalyzer.h "E:/My Documents/NetBeansProjects/Guitar_learning/LessonFile.pb.h" "E:/My Documents/NetBeansProjects/Guitar_learning/common.h" "E:/My Documents/NetBeansProjects/Guitar_learning/Metronome.h"
FORMS += Scholar.ui Tuner.ui Tutor.ui
RESOURCES += "E:/My Documents/NetBeansProjects/Guitar_learning/Sounds.qrc" Images.qrc
TRANSLATIONS +=
OBJECTS_DIR = build/Release/MinGW_1-Windows
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc.exe
QMAKE_CXX = g++.exe
DEFINES += 
INCLUDEPATH += 
LIBS += -lportaudio.dll -lprotobuf  
QT += multimedia
