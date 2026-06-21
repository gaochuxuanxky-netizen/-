#pragma once

#include "model/Project.h"

#include <QList>
#include <QStringList>

class ProjectService
{
public:
    QList<Project> getProjectList();
    bool addProject(Project &project);
    bool updateProject(const Project &project);
    bool deleteProject(int id);
    QStringList analyzeProjectTags() const;
};
