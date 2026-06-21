#pragma once

#include <QSqlDatabase>

// 单例模式：数据库连接与表初始化
class DatabaseManager
{
public:
    static DatabaseManager &instance();

    bool open();
    QSqlDatabase database() const;
    bool isOpen() const;

private:
    DatabaseManager();
    bool createTables();
    bool seedDefaultData();

    QSqlDatabase m_db;
    bool m_open = false;
};
