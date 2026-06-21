#pragma once

#include "model/Achievement.h"

#include <QList>

class AchievementService
{
public:
    QList<Achievement> getAchievementList();
    bool addAchievement(Achievement &achievement);
    bool updateAchievement(const Achievement &achievement);
    bool deleteAchievement(int id);
};
