#include "ProjectService.h"

#include "dao/ProjectDao.h"

QList<Project> ProjectService::getProjectList()
{
    return ProjectDao().findAll();
}

bool ProjectService::addProject(Project &project)
{
    if (!project.isValid()) return false;
    return ProjectDao().insert(project);
}

bool ProjectService::updateProject(const Project &project)
{
    if (!project.isValid() || project.id < 0) return false;
    return ProjectDao().update(project);
}

bool ProjectService::deleteProject(int id)
{
    return ProjectDao().remove(id);
}

QStringList ProjectService::analyzeProjectTags() const
{
    QStringList tags;
    for (const Project &p : ProjectDao().findAll()) {
        for (const QString &t : p.tags) {
            if (!tags.contains(t)) tags.append(t);
        }
    }
    return tags;
}
