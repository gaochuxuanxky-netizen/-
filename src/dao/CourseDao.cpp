#include "CourseDao.h"

#include "dao/DatabaseManager.h"

#include <QSqlQuery>

QList<Course> CourseDao::findAll()
{
    QList<Course> list;
    QSqlQuery q(DatabaseManager::instance().database());
    q.exec(QStringLiteral("SELECT id,course_name,credit,score,semester,category,teacher FROM courses ORDER BY id"));
    while (q.next()) {
        Course c;
        c.id = q.value(0).toInt();
        c.courseName = q.value(1).toString();
        c.credit = q.value(2).toDouble();
        c.score = q.value(3).toDouble();
        c.semester = q.value(4).toString();
        c.category = q.value(5).toString();
        c.teacher = q.value(6).toString();
        list.append(c);
    }
    return list;
}

bool CourseDao::insert(Course &course)
{
    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral(
        "INSERT INTO courses (course_name,credit,score,semester,category,teacher) VALUES (?,?,?,?,?,?)"));
    q.addBindValue(course.courseName);
    q.addBindValue(course.credit);
    q.addBindValue(course.score);
    q.addBindValue(course.semester);
    q.addBindValue(course.category);
    q.addBindValue(course.teacher);
    if (!q.exec()) return false;
    course.id = q.lastInsertId().toInt();
    return true;
}

bool CourseDao::update(const Course &course)
{
    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral(
        "UPDATE courses SET course_name=?,credit=?,score=?,semester=?,category=?,teacher=? WHERE id=?"));
    q.addBindValue(course.courseName);
    q.addBindValue(course.credit);
    q.addBindValue(course.score);
    q.addBindValue(course.semester);
    q.addBindValue(course.category);
    q.addBindValue(course.teacher);
    q.addBindValue(course.id);
    return q.exec();
}

bool CourseDao::remove(int id)
{
    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral("DELETE FROM courses WHERE id=?"));
    q.addBindValue(id);
    return q.exec();
}
