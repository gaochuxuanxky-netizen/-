#include "AchievementDao.h"

#include "dao/DatabaseManager.h"

#include <QSqlQuery>

QList<Achievement> AchievementDao::findAll()
{
    QList<Achievement> list;
    QSqlQuery q(DatabaseManager::instance().database());
    q.exec(QStringLiteral(
        "SELECT id,award_name,award_level,award_date,certificate,description FROM achievements ORDER BY id"));
    while (q.next()) {
        Achievement a;
        a.id = q.value(0).toInt();
        a.awardName = q.value(1).toString();
        a.awardLevel = q.value(2).toString();
        a.awardDate = q.value(3).toString();
        a.certificate = q.value(4).toString();
        a.description = q.value(5).toString();
        list.append(a);
    }
    return list;
}

bool AchievementDao::insert(Achievement &achievement)
{
    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral(
        "INSERT INTO achievements (award_name,award_level,award_date,certificate,description) VALUES (?,?,?,?,?)"));
    q.addBindValue(achievement.awardName);
    q.addBindValue(achievement.awardLevel);
    q.addBindValue(achievement.awardDate);
    q.addBindValue(achievement.certificate);
    q.addBindValue(achievement.description);
    if (!q.exec()) return false;
    achievement.id = q.lastInsertId().toInt();
    return true;
}

bool AchievementDao::update(const Achievement &achievement)
{
    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral(
        "UPDATE achievements SET award_name=?,award_level=?,award_date=?,certificate=?,description=? WHERE id=?"));
    q.addBindValue(achievement.awardName);
    q.addBindValue(achievement.awardLevel);
    q.addBindValue(achievement.awardDate);
    q.addBindValue(achievement.certificate);
    q.addBindValue(achievement.description);
    q.addBindValue(achievement.id);
    return q.exec();
}

bool AchievementDao::remove(int id)
{
    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral("DELETE FROM achievements WHERE id=?"));
    q.addBindValue(id);
    return q.exec();
}
