#include "PathAnalyzer.h"

#include "dao/AchievementDao.h"
#include "dao/CourseDao.h"
#include "dao/ProjectDao.h"
#include "patterns/ConfigManager.h"
#include "patterns/GpaStrategy.h"
#include "service/CourseService.h"

#include <algorithm>
#include <cmath>
#include <memory>

AbilityScore PathAnalyzer::analyzeAbility() const
{
    const QList<Course> courses = CourseDao().findAll();
    const QList<Project> projects = ProjectDao().findAll();
    const QList<Achievement> achievements = AchievementDao().findAll();

    CourseService cs;
    const double gpa = cs.calculateGpa(ConfigManager::instance().gpaStrategy());
    const double avg = cs.averageScore(courses);

    AbilityScore a;
    a.academic = std::min(100, static_cast<int>(std::round(avg * 0.9 + gpa * 6)));
    a.practice = std::min(100, static_cast<int>(projects.size() * 22 + [&projects]() {
        int s = 0;
        for (const Project &p : projects) s += p.impact * 4;
        return s;
    }()));
    a.innovation = std::min(100, static_cast<int>([&projects, &achievements]() {
        int cnt = 0;
        for (const Project &p : projects) {
            if (p.projectType.contains(QStringLiteral("科研")) ||
                p.projectType.contains(QStringLiteral("创新")) ||
                p.projectType.contains(QStringLiteral("竞赛")))
                ++cnt;
        }
        return cnt * 28 + static_cast<int>(achievements.size()) * 12;
    }()));
    a.honor = std::min(100, static_cast<int>(static_cast<int>(achievements.size()) * 25 + [&achievements]() {
        int cnt = 0;
        for (const Achievement &x : achievements) {
            if (x.awardLevel == QStringLiteral("国家级") || x.awardLevel == QStringLiteral("省级")) ++cnt;
        }
        return cnt * 18;
    }()));
    a.overall = static_cast<int>(std::round(a.academic * 0.35 + a.practice * 0.3 + a.innovation * 0.2 + a.honor * 0.15));
    return a;
}

QList<Suggestion> PathAnalyzer::generateSuggestion(const QString &target) const
{
    const AbilityScore a = analyzeAbility();
    QList<Suggestion> list;

    auto push = [&](const QString &prio, const QString &title, const QString &detail) {
        list.append({prio, title, detail});
    };

    if (a.academic < 82) {
        const bool highAcademic = target == QStringLiteral("postgraduate-exam") ||
                                  target == QStringLiteral("civil-service") ||
                                  target == QStringLiteral("study-abroad");
        push(highAcademic ? QStringLiteral("高优先级") : QStringLiteral("中优先级"),
             QStringLiteral("提升学业表现与核心课程成绩"),
             QStringLiteral("建议优先复盘专业核心课程，建立错题与知识点清单，将 GPA 稳定提升到目标方向要求区间。"));
    }
    if (a.practice < 70) {
        push(target == QStringLiteral("internet-job") ? QStringLiteral("高优先级") : QStringLiteral("中优先级"),
             QStringLiteral("补充项目与实习实践经历"),
             QStringLiteral("建议选择 1-2 个可展示成果的实践项目，明确个人角色、技术栈、量化结果，并沉淀作品集。"));
    }
    if (a.innovation < 60 && target != QStringLiteral("internet-job")) {
        push(target == QStringLiteral("research-track") ? QStringLiteral("高优先级") : QStringLiteral("中优先级"),
             QStringLiteral("增强科研与竞赛创新能力"),
             QStringLiteral("可参与导师课题、学科竞赛或大学生创新训练项目，积累论文、专利、竞赛作品等证明材料。"));
    }
    if (a.honor < 55) {
        push(QStringLiteral("低优先级"),
             QStringLiteral("系统整理荣誉奖项与综合素质材料"),
             QStringLiteral("建议按国家级、省级、校级、院级分类管理证书，补充获奖时间、贡献说明和证明文件。"));
    }
    if (list.isEmpty()) {
        push(QStringLiteral("中优先级"),
             QStringLiteral("当前能力结构较均衡"),
             QStringLiteral("建议继续保持数据记录习惯，并围绕目标方向打造 1 个高质量代表性项目或成果。"));
    }
    return list;
}

QString PathAnalyzer::analyzeGpa() const
{
    CourseService cs;
    const double gpa = cs.calculateGpa(ConfigManager::instance().gpaStrategy());
    if (gpa >= 3.5) return QStringLiteral("学业表现优秀，GPA 处于较高水平。");
    if (gpa >= 3.0) return QStringLiteral("学业表现良好，仍有提升空间。");
    if (gpa >= 2.5) return QStringLiteral("GPA 偏低，建议加强核心课程学习。");
    return QStringLiteral("GPA 明显不足，需优先提升学业成绩。");
}

QString PathAnalyzer::detectGap(const QString &target) const
{
    const AbilityScore a = analyzeAbility();
    QStringList gaps;
    if (target == QStringLiteral("postgraduate-exam") && a.academic < 85)
        gaps << QStringLiteral("考研方向要求较高学业能力，当前学业评分偏低。");
    if (target == QStringLiteral("internet-job") && a.practice < 75)
        gaps << QStringLiteral("就业方向需要更多项目与实习经历支撑。");
    if (target == QStringLiteral("research-track") && a.innovation < 70)
        gaps << QStringLiteral("科研方向需要更多竞赛、科研或创新项目。");
    if (target == QStringLiteral("civil-service") && a.academic < 80)
        gaps << QStringLiteral("考公方向需要扎实的公共基础与专业素养，当前学业评分仍有提升空间。");
    if (target == QStringLiteral("study-abroad") && a.academic < 88)
        gaps << QStringLiteral("出国方向通常要求更高 GPA 与语言/科研背景，建议加强学业与国际化经历。");
    if (gaps.isEmpty()) return QStringLiteral("当前能力与目标方向基本匹配，可继续深化优势领域。");
    return gaps.join(QStringLiteral("\n"));
}
