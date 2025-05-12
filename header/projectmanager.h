#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <qobject.h>
#include "treenode.h"
#include "graphicsitem.h"
class ProjectManager {
public:
    void createProject();
    bool openProject(const QString &filePath);
    bool saveProject(const QString &filePath);

    void newGraphicsView();
    void newTreeViewModel();
    void resetManager();
    void resetSceneController();
    void resetDrawController();

private:
    void fillTreeNodeFromJson(TreeNode *node, const QJsonObject &obj);
    TreeNode *deserializeTreeNode(const QJsonObject &obj);
    QJsonObject serializeTreeNode(TreeNode *node);
    std::shared_ptr < GraphicsItem > createGraphicsItemFromJson(const QJsonObject &obj);


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
