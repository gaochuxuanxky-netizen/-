#pragma once

#include <QString>

struct AbilityScore
{
    int academic = 0;
    int practice = 0;
    int innovation = 0;
    int honor = 0;
    int overall = 0;
};

struct Suggestion
{
    QString priority;
    QString title;
    QString detail;
};

class PathAnalyzer
{
public:
    AbilityScore analyzeAbility() const;
    QList<Suggestion> generateSuggestion(const QString &target) const;
    QString analyzeGpa() const;
    QString detectGap(const QString &target) const;
};
