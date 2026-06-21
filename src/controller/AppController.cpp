#include "AppController.h"

#include "dao/DatabaseManager.h"
#include "dao/UserDao.h"
#include "patterns/ConfigManager.h"
#include "patterns/DataFactory.h"
#include "service/AchievementService.h"
#include "service/CourseService.h"
#include "service/PathAnalyzer.h"
#include "service/ProjectService.h"
#include "service/ResumeGenerator.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

AppController::AppController(QObject *parent)
    : QObject(parent)
{
    DatabaseManager::instance().open();
    m_user = UserDao().load();
}

User AppController::user() const
{
    return m_user;
}

bool AppController::saveUser(const User &user)
{
    if (user.name.trimmed().isEmpty()) return false;
    if (!UserDao().save(user)) return false;
    m_user = user;
    emit dataChanged();
    return true;
}

QList<Course> AppController::courses() const
{
    return CourseService().getCourseList();
}

bool AppController::addCourse(Course &course)
{
    if (!CourseService().addCourse(course)) return false;
    emit dataChanged();
    return true;
}

bool AppController::updateCourse(const Course &course)
{
    if (!CourseService().updateCourse(course)) return false;
    emit dataChanged();
    return true;
}

bool AppController::deleteCourse(int id)
{
    if (!CourseService().deleteCourse(id)) return false;
    emit dataChanged();
    return true;
}

QList<Project> AppController::projects() const
{
    return ProjectService().getProjectList();
}

bool AppController::addProject(Project &project)
{
    if (!ProjectService().addProject(project)) return false;
    emit dataChanged();
    return true;
}

bool AppController::updateProject(const Project &project)
{
    if (!ProjectService().updateProject(project)) return false;
    emit dataChanged();
    return true;
}

bool AppController::deleteProject(int id)
{
    if (!ProjectService().deleteProject(id)) return false;
    emit dataChanged();
    return true;
}

QList<Achievement> AppController::achievements() const
{
    return AchievementService().getAchievementList();
}

bool AppController::addAchievement(Achievement &achievement)
{
    if (!AchievementService().addAchievement(achievement)) return false;
    emit dataChanged();
    return true;
}

bool AppController::updateAchievement(const Achievement &achievement)
{
    if (!AchievementService().updateAchievement(achievement)) return false;
    emit dataChanged();
    return true;
}

bool AppController::deleteAchievement(int id)
{
    if (!AchievementService().deleteAchievement(id)) return false;
    emit dataChanged();
    return true;
}

double AppController::gpa() const
{
    return CourseService().calculateGpa(ConfigManager::instance().gpaStrategy());
}

void AppController::setGpaStrategy(const QString &key)
{
    ConfigManager::instance().setGpaStrategy(key);
    emit dataChanged();
}

QString AppController::gpaStrategy() const
{
    return ConfigManager::instance().gpaStrategy();
}

AbilityScore AppController::analyzeAbility() const
{
    return PathAnalyzer().analyzeAbility();
}

QList<Suggestion> AppController::suggestions() const
{
    return PathAnalyzer().generateSuggestion(m_user.target);
}

QString AppController::resumeText() const
{
    return ResumeGenerator().generateResume();
}

bool AppController::exportResume(const QString &path) const
{
    return ResumeGenerator().exportToFile(path);
}

bool AppController::exportJson(const QString &path) const
{
    QJsonObject root;
    QJsonObject profile;
    profile.insert(QStringLiteral("name"), m_user.name);
    profile.insert(QStringLiteral("studentId"), m_user.studentId);
    profile.insert(QStringLiteral("school"), m_user.school);
    profile.insert(QStringLiteral("major"), m_user.major);
    profile.insert(QStringLiteral("grade"), m_user.grade);
    profile.insert(QStringLiteral("phone"), m_user.phone);
    profile.insert(QStringLiteral("email"), m_user.email);
    profile.insert(QStringLiteral("target"), m_user.target);
    root.insert(QStringLiteral("profile"), profile);

    QJsonArray courseArr;
    for (const Course &c : courses()) {
        QJsonObject o;
        o.insert(QStringLiteral("name"), c.courseName);
        o.insert(QStringLiteral("credit"), c.credit);
        o.insert(QStringLiteral("score"), c.score);
        o.insert(QStringLiteral("category"), c.category);
        o.insert(QStringLiteral("semester"), c.semester);
        courseArr.append(o);
    }
    root.insert(QStringLiteral("courses"), courseArr);

    QJsonArray projectArr;
    for (const Project &p : projects()) {
        QJsonObject o;
        o.insert(QStringLiteral("name"), p.projectName);
        o.insert(QStringLiteral("type"), p.projectType);
        o.insert(QStringLiteral("role"), p.role);
        o.insert(QStringLiteral("description"), p.description);
        o.insert(QStringLiteral("tags"), QJsonArray::fromStringList(p.tags));
        o.insert(QStringLiteral("impact"), p.impact);
        projectArr.append(o);
    }
    root.insert(QStringLiteral("projects"), projectArr);

    QJsonArray achArr;
    for (const Achievement &a : achievements()) {
        QJsonObject o;
        o.insert(QStringLiteral("name"), a.awardName);
        o.insert(QStringLiteral("level"), a.awardLevel);
        o.insert(QStringLiteral("date"), a.awardDate);
        o.insert(QStringLiteral("description"), a.description);
        achArr.append(o);
    }
    root.insert(QStringLiteral("achievements"), achArr);

    QFile f(path);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) return false;
    f.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    return true;
}

bool AppController::importJson(const QString &path, QString *error)
{
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly)) {
        if (error) *error = QStringLiteral("无法打开文件");
        return false;
    }
    const QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    if (!doc.isObject()) {
        if (error) *error = QStringLiteral("JSON 格式无效");
        return false;
    }
    const QJsonObject root = doc.object();

    if (root.contains(QStringLiteral("profile"))) {
        const QJsonObject p = root.value(QStringLiteral("profile")).toObject();
        User u = m_user;
        u.name = p.value(QStringLiteral("name")).toString(u.name);
        u.studentId = p.value(QStringLiteral("studentId")).toString(u.studentId);
        u.school = p.value(QStringLiteral("school")).toString(u.school);
        u.major = p.value(QStringLiteral("major")).toString(u.major);
        u.grade = p.value(QStringLiteral("grade")).toString(u.grade);
        u.phone = p.value(QStringLiteral("phone")).toString(u.phone);
        u.email = p.value(QStringLiteral("email")).toString(u.email);
        u.target = p.value(QStringLiteral("target")).toString(u.target);
        if (!saveUser(u)) {
            if (error) *error = QStringLiteral("用户信息保存失败");
            return false;
        }
    }

    for (const Course &c : courses()) deleteCourse(c.id);
    for (const QJsonValue &v : root.value(QStringLiteral("courses")).toArray()) {
        const QJsonObject o = v.toObject();
        Course c = DataFactory::createCourse(o.value(QStringLiteral("name")).toString());
        c.credit = o.value(QStringLiteral("credit")).toDouble(c.credit);
        c.score = o.value(QStringLiteral("score")).toDouble(c.score);
        c.category = o.value(QStringLiteral("category")).toString(c.category);
        c.semester = o.value(QStringLiteral("semester")).toString(c.semester);
        addCourse(c);
    }

    for (const Project &p : projects()) deleteProject(p.id);
    for (const QJsonValue &v : root.value(QStringLiteral("projects")).toArray()) {
        const QJsonObject o = v.toObject();
        Project p = DataFactory::createProject(o.value(QStringLiteral("name")).toString());
        p.projectType = o.value(QStringLiteral("type")).toString(p.projectType);
        p.role = o.value(QStringLiteral("role")).toString(p.role);
        p.description = o.value(QStringLiteral("description")).toString(p.description);
        p.impact = o.value(QStringLiteral("impact")).toInt(p.impact);
        const QJsonArray tags = o.value(QStringLiteral("tags")).toArray();
        p.tags.clear();
        for (const QJsonValue &t : tags) p.tags.append(t.toString());
        addProject(p);
    }

    for (const Achievement &a : achievements()) deleteAchievement(a.id);
    for (const QJsonValue &v : root.value(QStringLiteral("achievements")).toArray()) {
        const QJsonObject o = v.toObject();
        Achievement a = DataFactory::createAchievement(o.value(QStringLiteral("name")).toString());
        a.awardLevel = o.value(QStringLiteral("level")).toString(a.awardLevel);
        a.awardDate = o.value(QStringLiteral("date")).toString(a.awardDate);
        a.description = o.value(QStringLiteral("description")).toString(a.description);
        addAchievement(a);
    }

    emit dataChanged();
    return true;
}

bool AppController::backupDatabase(const QString &path) const
{
    return QFile::copy(ConfigManager::instance().dbPath(), path);
}
