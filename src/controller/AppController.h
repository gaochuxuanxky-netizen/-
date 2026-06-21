#pragma once

#include "model/Achievement.h"
#include "model/Course.h"
#include "model/Project.h"
#include "model/User.h"
#include "service/PathAnalyzer.h"

#include <QObject>
#include <QString>

// 控制层：请求调度、参数校验、调用业务服务
class AppController : public QObject
{
    Q_OBJECT

public:
    explicit AppController(QObject *parent = nullptr);

    User user() const;
    bool saveUser(const User &user);

    QList<Course> courses() const;
    bool addCourse(Course &course);
    bool updateCourse(const Course &course);
    bool deleteCourse(int id);

    QList<Project> projects() const;
    bool addProject(Project &project);
    bool updateProject(const Project &project);
    bool deleteProject(int id);

    QList<Achievement> achievements() const;
    bool addAchievement(Achievement &achievement);
    bool updateAchievement(const Achievement &achievement);
    bool deleteAchievement(int id);

    double gpa() const;
    void setGpaStrategy(const QString &key);
    QString gpaStrategy() const;

    AbilityScore analyzeAbility() const;
    QList<Suggestion> suggestions() const;
    QString resumeText() const;

    bool exportResume(const QString &path) const;
    bool exportJson(const QString &path) const;
    bool importJson(const QString &path, QString *error = nullptr);
    bool backupDatabase(const QString &path) const;

signals:
    void dataChanged();

private:
    User m_user;
};
