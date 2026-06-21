#pragma once

#include <QString>

class Course;
class Project;
class Achievement;

// 工厂模式：统一创建业务对象
class DataFactory
{
public:
    static Course createCourse(const QString &name = QString());
    static Project createProject(const QString &name = QString());
    static Achievement createAchievement(const QString &name = QString());
};
