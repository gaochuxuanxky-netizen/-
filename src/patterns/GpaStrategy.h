#pragma once

#include <QList>
#include <QString>

class Course;

// 策略模式：多种 GPA 计算规则
class IGpaStrategy
{
public:
    virtual ~IGpaStrategy() = default;
    virtual QString name() const = 0;
    virtual double calculate(const QList<Course> &courses) const = 0;
};

class Standard4GpaStrategy : public IGpaStrategy
{
public:
    QString name() const override { return QStringLiteral("标准 4.0 制"); }
    double calculate(const QList<Course> &courses) const override;
};

class Peking45GpaStrategy : public IGpaStrategy
{
public:
    QString name() const override { return QStringLiteral("北大 4.5 制"); }
    double calculate(const QList<Course> &courses) const override;
};

class WeightedAverageStrategy : public IGpaStrategy
{
public:
    QString name() const override { return QStringLiteral("加权平均分"); }
    double calculate(const QList<Course> &courses) const override;
};

class GpaStrategyFactory
{
public:
    static IGpaStrategy *create(const QString &key);
    static QStringList availableKeys();
    static QString labelForKey(const QString &key);
};
