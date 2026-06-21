#pragma once

#include "model/Achievement.h"

#include <QList>

class AchievementDao
{
public:
    QList<Achievement> findAll();
    bool insert(Achievement &achievement);
    bool update(const Achievement &achievement);
    bool remove(int id);
};
