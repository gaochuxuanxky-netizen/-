#include "DataFactory.h"

#include "model/Achievement.h"
#include "model/Course.h"
#include "model/Project.h"

Course DataFactory::createCourse(const QString &name)
{
    Course c;
    c.courseName = name.isEmpty() ? QStringLiteral("新课程") : name;
    c.credit = 2;
    c.score = 80;
    c.category = QStringLiteral("专业课程");
    c.semester = QStringLiteral("2025-2026-1");
    return c;
}

Project DataFactory::createProject(const QString &name)
{
    Project p;
    p.projectName = name.isEmpty() ? QStringLiteral("新项目") : name;
    p.projectType = QStringLiteral("实践项目");
    p.role = QStringLiteral("成员");
    p.description = QStringLiteral("描述项目背景、个人贡献与结果。");
    p.tags = {QStringLiteral("待补充")};
    p.impact = 3;
    p.startDate = QStringLiteral("2025-09");
    p.endDate = QStringLiteral("2026-01");
    return p;
}

Achievement DataFactory::createAchievement(const QString &name)
{
    Achievement a;
    a.awardName = name.isEmpty() ? QStringLiteral("新荣誉") : name;
    a.awardLevel = QStringLiteral("校级");
    a.awardDate = QStringLiteral("2026-05");
    a.description = QStringLiteral("补充获奖背景与个人贡献。");
    return a;
}
