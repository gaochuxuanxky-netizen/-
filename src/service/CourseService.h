#pragma once

#include "model/Course.h"

#include <QList>
#include <QString>

class CourseService
{
public:
    QList<Course> getCourseList();
    bool addCourse(Course &course);
    bool updateCourse(const Course &course);
    bool deleteCourse(int id);
    double calculateGpa(const QString &strategyKey) const;
    double averageScore(const QList<Course> &courses) const;
    int totalCredits(const QList<Course> &courses) const;
};
