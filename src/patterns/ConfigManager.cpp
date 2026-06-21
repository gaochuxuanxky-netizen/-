#include "ConfigManager.h"

#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>

ConfigManager &ConfigManager::instance()
{
    static ConfigManager inst;
    return inst;
}

ConfigManager::ConfigManager() = default;

QString ConfigManager::dbPath() const
{
    const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    return dir + QStringLiteral("/smartpath.db");
}

QString ConfigManager::gpaStrategy() const
{
    return m_gpaStrategy;
}

void ConfigManager::setGpaStrategy(const QString &strategy)
{
    m_gpaStrategy = strategy;
}

QString ConfigManager::goalLabel(const QString &target)
{
    if (target == QStringLiteral("internet-job")) return QStringLiteral("互联网公司就业");
    if (target == QStringLiteral("postgraduate-exam")) return QStringLiteral("研究生考试");
    if (target == QStringLiteral("research-track")) return QStringLiteral("科研创新方向");
    if (target == QStringLiteral("civil-service")) return QStringLiteral("公务员考试");
    if (target == QStringLiteral("study-abroad")) return QStringLiteral("出国留学");
    return QStringLiteral("综合能力提升");
}
