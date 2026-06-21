#pragma once

#include "model/Course.h"

#include <QList>

class CourseDao
{
public:
    QList<Course> findAll();
    bool insert(Course &course);
    bool update(const Course &course);
    bool remove(int id);
};
