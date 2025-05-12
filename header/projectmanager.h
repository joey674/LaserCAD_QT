#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <qobject.h>
class ProjectManager {
public:
    void createProject();
    void openProject(const QString &filePath);
    void saveProject(const QString &filePath);

    void newGraphicsView();
    void newTreeViewModel();
    void resetManager();
    void resetSceneController();
    void resetDrawController();

private:
    // void clearScene();
    // void clearModel();

private:
    static ProjectManager ins;
    ProjectManager() {};
    ProjectManager(const ProjectManager &);
    ~ProjectManager() {};
    ProjectManager &operator=(const ProjectManager &);

public:
    static ProjectManager &getIns();
};

#endif // PROJECTMANAGER_H
