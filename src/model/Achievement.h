#pragma once

#include <QString>

class Achievement
{
public:
    int id = -1;
    QString awardName;
    QString awardLevel;
    QString awardDate;
    QString certificate;
    QString description;

    Achievement() = default;
    bool isValid() const { return !awardName.trimmed().isEmpty(); }
};
