#pragma once

#include "model/Project.h"

#include <QList>

class ProjectDao
{
public:
    QList<Project> findAll();
    bool insert(Project &project);
    bool update(const Project &project);
    bool remove(int id);
};
