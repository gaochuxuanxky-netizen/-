#pragma once

#include <QString>
#include <QStringList>

class Project
{
public:
    int id = -1;
    QString projectName;
    QString projectType;
    QString role;
    QString startDate;
    QString endDate;
    QString description;
    QStringList tags;
    int impact = 3;

    Project() = default;
    bool isValid() const { return !projectName.trimmed().isEmpty(); }
};
