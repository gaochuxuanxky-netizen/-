# SmartPath Qt 桌面版

根据《听老师的话小组期中报告》要求，使用 **Qt 6 + C++** 实现的 **SmartPath 大学生智能成长规划系统** 本地可执行程序。

## 系统架构（五层分层架构）

```text
表现层 (UI)          → src/ui/MainWindow.*
控制层 (Controller)  → src/controller/AppController.*
业务逻辑层 (Service) → src/service/*
数据访问层 (DAO)     → src/dao/*
数据存储层 (Database)→ SQLite (smartpath.db)
```

## 已实现功能

| 模块 | 说明 |
|------|------|
| 用户信息管理 | 姓名、学号、学校、专业、年级、联系方式、发展目标 |
| 课程与成绩管理 | 增删改查、输入校验 |
| GPA 自动计算 | **策略模式**：标准 4.0 / 北大 4.5 / 加权平均分 |
| 项目/竞赛/实习管理 | 标签分类、影响力评分 |
| 荣誉奖项管理 | 等级分类、说明记录 |
| 智能路径分析 | 能力评估、目标差距检测、个性化建议（核心创新） |
| 简历自动生成 | 整合全部数据，支持导出 TXT、复制 |
| 数据持久化 | SQLite 本地存储 |
| 数据导入/导出 | JSON 导出、JSON 导入、数据库备份 |

## 设计模式

- **单例模式**：`ConfigManager`（配置）、`DatabaseManager`（数据库连接）
- **工厂模式**：`DataFactory`（创建课程/项目/荣誉对象）
- **策略模式**：`GpaStrategy`（多种 GPA 算法切换）

## 环境要求

- Windows 10/11
- [Qt 6.x](https://www.qt.io/download)（含 Widgets、Sql 模块）
- CMake 3.16+
- 支持 C++17 的编译器（MSVC / MinGW）

## 编译与运行

### 方式零：直接运行（已打包）

桌面 `SmartPath-Qt\release\` 目录下已包含可执行程序，双击 **启动 SmartPath.bat** 或 **SmartPath.exe** 即可运行。

### 方式一：Qt Creator（推荐）

1. 安装 Qt 6 并勾选 **Qt Widgets**、**Qt Sql**
2. 打开 Qt Creator → **文件 → 打开文件或项目**
3. 选择 `CMakeLists.txt`
4. 配置 Kit（Desktop Qt 6.x MSVC/MinGW）
5. 点击 **运行**

### 方式二：命令行

```powershell
cd "C:\Users\YOGA\Desktop\作业\SmartPath-Qt"
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH="C:\Qt\6.8.0\msvc2022_64"
cmake --build . --config Release
.\Release\SmartPath.exe
```

请将 `CMAKE_PREFIX_PATH` 改为你本机 Qt 安装路径。

### 方式三：MSYS2 命令行（本机已验证）

```powershell
# 双击 build_msys.bat 编译，或手动执行：
C:\msys64\usr\bin\bash.exe -lc "export PATH=/ucrt64/bin:/usr/bin:$PATH && cd /c/Users/YOGA/Desktop/SmartPath-Qt/build_msys && cmake .. -DCMAKE_PREFIX_PATH=/ucrt64 -G Ninja && ninja"
```

打包发布：双击 `package_release.bat`

## 数据存储位置

程序首次运行后，数据库保存在：

```text
%APPDATA%\SmartPath\smartpath.db
```

## 与 Web 原型关系

- `SmartPath-Platform/`：HTML 静态原型（浏览器演示）
- `SmartPath-Qt/`：Qt 桌面完整实现（本目录，对应报告中的本地可执行版本）

## 小组信息

听老师的话小组：崔子平、高楚煊、黄睿淳、吉翔天
