#pragma once

#include <QString>

// 单例模式：系统配置管理
class ConfigManager
{
public:
    static ConfigManager &instance();

    QString dbPath() const;
    QString gpaStrategy() const;
    void setGpaStrategy(const QString &strategy);

    static QString goalLabel(const QString &target);

private:
    ConfigManager();
    QString m_gpaStrategy = QStringLiteral("standard4");
};
