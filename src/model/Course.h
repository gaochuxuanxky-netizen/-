#pragma once

#include <QString>

class Course
{
public:
    int id = -1;
    QString courseName;
    double credit = 0;
    double score = 0;
    QString semester;
    QString category;
    QString teacher;

    Course() = default;
    bool isValid() const
    {
        return !courseName.trimmed().isEmpty() && credit > 0 && score >= 0 && score <= 100;
    }
};
