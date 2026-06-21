#include "UserDao.h"

#include "dao/DatabaseManager.h"

#include <QSqlQuery>

User UserDao::load()
{
    User u;
    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral("SELECT name,student_id,school,major,grade,phone,email,target FROM user_info WHERE id=1"));
    if (q.exec() && q.next()) {
        u.name = q.value(0).toString();
        u.studentId = q.value(1).toString();
        u.school = q.value(2).toString();
        u.major = q.value(3).toString();
        u.grade = q.value(4).toString();
        u.phone = q.value(5).toString();
        u.email = q.value(6).toString();
        u.target = q.value(7).toString();
    }
    return u;
}

bool UserDao::save(const User &user)
{
    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral(
        "UPDATE user_info SET name=?, student_id=?, school=?, major=?, grade=?, phone=?, email=?, target=? WHERE id=1"));
    q.addBindValue(user.name);
    q.addBindValue(user.studentId);
    q.addBindValue(user.school);
    q.addBindValue(user.major);
    q.addBindValue(user.grade);
    q.addBindValue(user.phone);
    q.addBindValue(user.email);
    q.addBindValue(user.target);
    return q.exec();
}
