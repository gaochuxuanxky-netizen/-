#include "ProjectDao.h"

#include "dao/DatabaseManager.h"

#include <QSqlQuery>

QList<Project> ProjectDao::findAll()
{
    QList<Project> list;
    QSqlQuery q(DatabaseManager::instance().database());
    q.exec(QStringLiteral(
        "SELECT id,project_name,project_type,role,start_date,end_date,description,tags,impact FROM projects ORDER BY id"));
    while (q.next()) {
        Project p;
        p.id = q.value(0).toInt();
        p.projectName = q.value(1).toString();
        p.projectType = q.value(2).toString();
        p.role = q.value(3).toString();
        p.startDate = q.value(4).toString();
        p.endDate = q.value(5).toString();
        p.description = q.value(6).toString();
        p.tags = q.value(7).toString().split(',', Qt::SkipEmptyParts);
        for (QString &t : p.tags) t = t.trimmed();
        p.impact = q.value(8).toInt();
        list.append(p);
    }
    return list;
}

bool ProjectDao::insert(Project &project)
{
    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral(
        "INSERT INTO projects (project_name,project_type,role,start_date,end_date,description,tags,impact) "
        "VALUES (?,?,?,?,?,?,?,?)"));
    q.addBindValue(project.projectName);
    q.addBindValue(project.projectType);
    q.addBindValue(project.role);
    q.addBindValue(project.startDate);
    q.addBindValue(project.endDate);
    q.addBindValue(project.description);
    q.addBindValue(project.tags.join(QStringLiteral(",")));
    q.addBindValue(project.impact);
    if (!q.exec()) return false;
    project.id = q.lastInsertId().toInt();
    return true;
}

bool ProjectDao::update(const Project &project)
{
    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral(
        "UPDATE projects SET project_name=?,project_type=?,role=?,start_date=?,end_date=?,description=?,tags=?,impact=? "
        "WHERE id=?"));
    q.addBindValue(project.projectName);
    q.addBindValue(project.projectType);
    q.addBindValue(project.role);
    q.addBindValue(project.startDate);
    q.addBindValue(project.endDate);
    q.addBindValue(project.description);
    q.addBindValue(project.tags.join(QStringLiteral(",")));
    q.addBindValue(project.impact);
    q.addBindValue(project.id);
    return q.exec();
}

bool ProjectDao::remove(int id)
{
    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral("DELETE FROM projects WHERE id=?"));
    q.addBindValue(id);
    return q.exec();
}
