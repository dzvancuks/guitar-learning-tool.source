/* 
 * File:   LoadStore.h
 * Author: astral
 *
 * Created on 20 Октябрь 2012 г., 14:44
 */

/*
 * run "protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/LessonFile.proto"
 * [IN]
 * LessonFile.proto - storage file description
 * [OUT]
 * LessonFile.pb.h - generated structures (2500 LoC!)
 * LessonFile.pb.cc - generated methods (3500 LoC!)
 */

#ifndef LOADSTORE_H
#define	LOADSTORE_H

#include <iostream>
#include <QFile>
#include <QString>
#include <stdlib.h>

#include "LessonFile.pb.h"
#include "Lesson.h"

using namespace Guitar_learning;

#define MAX64K 65536

/* Static class that acts like middleware between NoteSystem and savefiles */
class LoadStore {
public:
    // [IN] Lesson *lesson, [IN] QFile *file
    static void Store(Lesson *lesson, QFile *file);
    // [OUT] Lesson *lesson, [IN] QFile *file
    static void Load(Lesson **dp_lesson, QFile *file);
};

#endif	/* LOADSTORE_H */

