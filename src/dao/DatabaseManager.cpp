#include "DatabaseManager.h"

#include "patterns/ConfigManager.h"

#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager inst;
    return inst;
}

DatabaseManager::DatabaseManager()
{
    m_db = QSqlDatabase::addDatabase(QStringLiteral("QSQLITE"));
    m_db.setDatabaseName(ConfigManager::instance().dbPath());
}

bool DatabaseManager::open()
{
    if (m_open) return true;
    if (!m_db.open()) return false;
    m_open = createTables() && seedDefaultData();
    return m_open;
}

QSqlDatabase DatabaseManager::database() const
{
    return m_db;
}

bool DatabaseManager::isOpen() const
{
    return m_open;
}

bool DatabaseManager::createTables()
{
    QSqlQuery q(m_db);
    const char *sql =
        "CREATE TABLE IF NOT EXISTS user_info ("
        "id INTEGER PRIMARY KEY CHECK (id = 1),"
        "name TEXT, student_id TEXT, school TEXT, major TEXT, grade TEXT,"
        "phone TEXT, email TEXT, target TEXT);"
        "CREATE TABLE IF NOT EXISTS courses ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "course_name TEXT, credit REAL, score REAL, semester TEXT, category TEXT, teacher TEXT);"
        "CREATE TABLE IF NOT EXISTS projects ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "project_name TEXT, project_type TEXT, role TEXT, start_date TEXT, end_date TEXT,"
        "description TEXT, tags TEXT, impact INTEGER);"
        "CREATE TABLE IF NOT EXISTS achievements ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "award_name TEXT, award_level TEXT, award_date TEXT, certificate TEXT, description TEXT);";

    if (!q.exec(sql)) return false;
    return true;
}

bool DatabaseManager::seedDefaultData()
{
    QSqlQuery q(m_db);
    q.prepare(QStringLiteral("SELECT COUNT(*) FROM user_info"));
    if (!q.exec() || !q.next()) return false;
    if (q.value(0).toInt() > 0) return true;

    q.prepare(QStringLiteral(
        "INSERT INTO user_info (id,name,student_id,school,major,grade,phone,email,target) "
        "VALUES (1,?,?,?,?,?,?,?,?)"));
    q.addBindValue(QStringLiteral("张同学"));
    q.addBindValue(QStringLiteral("20230001"));
    q.addBindValue(QStringLiteral("示例大学"));
    q.addBindValue(QStringLiteral("计算机科学与技术"));
    q.addBindValue(QStringLiteral("大三"));
    q.addBindValue(QString());
    q.addBindValue(QString());
    q.addBindValue(QStringLiteral("internet-job"));
    if (!q.exec()) return false;

    struct SeedCourse { const char *n; double cr; double sc; const char *cat; };
    const SeedCourse seedCourses[] = {
        {"数据结构", 4, 88, "专业核心"},
        {"数据库系统", 3, 91, "专业核心"},
        {"软件工程", 3, 86, "工程实践"},
    };
    for (const auto &c : seedCourses) {
        QSqlQuery ins(m_db);
        ins.prepare(QStringLiteral(
            "INSERT INTO courses (course_name,credit,score,semester,category,teacher) VALUES (?,?,?,?,?,?)"));
        ins.addBindValue(QString::fromUtf8(c.n));
        ins.addBindValue(c.cr);
        ins.addBindValue(c.sc);
        ins.addBindValue(QStringLiteral("2025-2026-1"));
        ins.addBindValue(QString::fromUtf8(c.cat));
        ins.addBindValue(QString());
        if (!ins.exec()) return false;
    }

    QSqlQuery p(m_db);
    p.prepare(QStringLiteral(
        "INSERT INTO projects (project_name,project_type,role,start_date,end_date,description,tags,impact) "
        "VALUES (?,?,?,?,?,?,?,?)"));
    p.addBindValue(QStringLiteral("SmartPath 成长规划系统"));
    p.addBindValue(QStringLiteral("课程项目"));
    p.addBindValue(QStringLiteral("产品与前端开发"));
    p.addBindValue(QStringLiteral("2025-09"));
    p.addBindValue(QStringLiteral("2026-01"));
    p.addBindValue(QStringLiteral("面向大学生的个人发展数据管理、能力评估与简历生成平台。"));
    p.addBindValue(QStringLiteral("Qt,C++,数据分析,规划系统"));
    p.addBindValue(4);
    if (!p.exec()) return false;

    QSqlQuery a(m_db);
    a.prepare(QStringLiteral(
        "INSERT INTO achievements (award_name,award_level,award_date,certificate,description) VALUES (?,?,?,?,?)"));
    a.addBindValue(QStringLiteral("校级创新项目立项"));
    a.addBindValue(QStringLiteral("校级"));
    a.addBindValue(QStringLiteral("2025-10"));
    a.addBindValue(QString());
    a.addBindValue(QStringLiteral("参与大学生创新训练计划，完成系统原型设计。"));
    return a.exec();
}
