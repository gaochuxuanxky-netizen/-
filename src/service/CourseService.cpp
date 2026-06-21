#include "CourseService.h"

#include "dao/CourseDao.h"
#include "patterns/GpaStrategy.h"

#include <cmath>
#include <memory>

QList<Course> CourseService::getCourseList()
{
    return CourseDao().findAll();
}

bool CourseService::addCourse(Course &course)
{
    if (!course.isValid()) return false;
    return CourseDao().insert(course);
}

bool CourseService::updateCourse(const Course &course)
{
    if (!course.isValid() || course.id < 0) return false;
    return CourseDao().update(course);
}

bool CourseService::deleteCourse(int id)
{
    return CourseDao().remove(id);
}

double CourseService::calculateGpa(const QString &strategyKey) const
{
    const QList<Course> courses = CourseDao().findAll();
    std::unique_ptr<IGpaStrategy> strategy(GpaStrategyFactory::create(strategyKey));
    return strategy->calculate(courses);
}

double CourseService::averageScore(const QList<Course> &courses) const
{
    if (courses.isEmpty()) return 0;
    double sum = 0;
    for (const Course &c : courses) sum += c.score;
    return std::round(sum / courses.size());
}

int CourseService::totalCredits(const QList<Course> &courses) const
{
    int sum = 0;
    for (const Course &c : courses) sum += static_cast<int>(c.credit);
    return sum;
}
