#include "AchievementService.h"

#include "dao/AchievementDao.h"

QList<Achievement> AchievementService::getAchievementList()
{
    return AchievementDao().findAll();
}

bool AchievementService::addAchievement(Achievement &achievement)
{
    if (!achievement.isValid()) return false;
    return AchievementDao().insert(achievement);
}

bool AchievementService::updateAchievement(const Achievement &achievement)
{
    if (!achievement.isValid() || achievement.id < 0) return false;
    return AchievementDao().update(achievement);
}

bool AchievementService::deleteAchievement(int id)
{
    return AchievementDao().remove(id);
}
