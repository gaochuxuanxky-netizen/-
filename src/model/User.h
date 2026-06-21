#pragma once

#include <QString>

class User
{
public:
    QString name;
    QString studentId;
    QString school;
    QString major;
    QString grade;
    QString phone;
    QString email;
    QString target; // internet-job, postgraduate-exam, research-track, general-growth

    User() = default;
    bool isValid() const { return !name.trimmed().isEmpty(); }
};
