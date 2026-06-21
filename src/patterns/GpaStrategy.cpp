#include "GpaStrategy.h"

#include "model/Course.h"

#include <algorithm>
#include <cmath>
#include <memory>

static double creditSum(const QList<Course> &courses)
{
    double sum = 0;
    for (const Course &c : courses) sum += c.credit;
    return sum;
}

double Standard4GpaStrategy::calculate(const QList<Course> &courses) const
{
    const double credits = creditSum(courses);
    if (credits <= 0) return 0;

    double points = 0;
    for (const Course &c : courses) {
        const double point = c.score >= 60 ? std::min(4.0, std::max(1.0, (c.score - 50.0) / 10.0)) : 0.0;
        points += point * c.credit;
    }
    return std::round(points / credits * 100.0) / 100.0;
}

double Peking45GpaStrategy::calculate(const QList<Course> &courses) const
{
    const double credits = creditSum(courses);
    if (credits <= 0) return 0;

    auto pointOf = [](double score) {
        if (score >= 100) return 4.5;
        if (score >= 90) return 4.0;
        if (score >= 85) return 3.7;
        if (score >= 82) return 3.3;
        if (score >= 78) return 3.0;
        if (score >= 75) return 2.7;
        if (score >= 72) return 2.3;
        if (score >= 68) return 2.0;
        if (score >= 64) return 1.5;
        if (score >= 60) return 1.0;
        return 0.0;
    };

    double points = 0;
    for (const Course &c : courses) points += pointOf(c.score) * c.credit;
    return std::round(points / credits * 100.0) / 100.0;
}

double WeightedAverageStrategy::calculate(const QList<Course> &courses) const
{
    const double credits = creditSum(courses);
    if (credits <= 0) return 0;

    double total = 0;
    for (const Course &c : courses) total += c.score * c.credit;
    return std::round(total / credits * 100.0) / 100.0;
}

IGpaStrategy *GpaStrategyFactory::create(const QString &key)
{
    if (key == QStringLiteral("peking45")) return new Peking45GpaStrategy();
    if (key == QStringLiteral("weighted")) return new WeightedAverageStrategy();
    return new Standard4GpaStrategy();
}

QStringList GpaStrategyFactory::availableKeys()
{
    return {QStringLiteral("standard4"), QStringLiteral("peking45"), QStringLiteral("weighted")};
}

QString GpaStrategyFactory::labelForKey(const QString &key)
{
    std::unique_ptr<IGpaStrategy> s(create(key));
    return s->name();
}
