cmake_minimum_required(VERSION 3.16)
project(SmartPath VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)

set(SOURCES
    src/main.cpp
    src/ui/MainWindow.cpp
    src/controller/AppController.cpp
    src/model/User.cpp
    src/model/Course.cpp
    src/model/Project.cpp
    src/model/Achievement.cpp
    src/dao/DatabaseManager.cpp
    src/dao/UserDao.cpp
    src/dao/CourseDao.cpp
    src/dao/ProjectDao.cpp
    src/dao/AchievementDao.cpp
    src/service/CourseService.cpp
    src/service/ProjectService.cpp
    src/service/AchievementService.cpp
    src/service/PathAnalyzer.cpp
    src/service/ResumeGenerator.cpp
    src/patterns/ConfigManager.cpp
    src/patterns/DataFactory.cpp
    src/patterns/GpaStrategy.cpp
)

add_executable(SmartPath ${SOURCES})

target_include_directories(SmartPath PRIVATE src)

target_link_libraries(SmartPath PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
)

if(WIN32)
    set_target_properties(SmartPath PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
