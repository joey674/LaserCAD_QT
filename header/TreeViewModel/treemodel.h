#ifndef TREEVIEWMODEL_H
#define TREEVIEWMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QMimeData>
#include <QIODevice>
#include "treenode.h"


class TreeModel : public QAbstractItemModel {
    Q_OBJECT
    friend class ProjectManager;
public:
    Q_DISABLE_COPY_MOVE(TreeModel)

    TreeModel(const QString &modelName, QObject *parent = nullptr);
    ~TreeModel() override;

    /// 获取/修改node名字
    QVariant data(const QModelIndex &nodeIndex, int role) const override;
    bool setData(const QModelIndex &nodeIndex, const QVariant &name, int role = Qt::EditRole) override;
    /// 获取/修改model名字
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;
    /// 获取node子节点的QModelIndex
    QModelIndex index(int row, int column, const QModelIndex &parentIndex = {}) const override;
    /// 获取node父节点的QModelIndex
    QModelIndex parent(const QModelIndex &nodeIndex) const override;
    /// 获取node的子节点个数
    int rowCount(const QModelIndex &nodeIndex = {}) const override;
    /// 使用的列数
    int columnCount(const QModelIndex &nodeIndex = QModelIndex()) const override;
    /// 插入/删除子节点
    bool insertRows(int insertPosition, int nodeCount, const QModelIndex &nodeIndex = {}) override;
    bool removeRows(int removePosition, int nodeCount, const QModelIndex &nodeIndex = {}) override;
    /// 控制节点的可操作选项;返回什么flag就说明item可以进行什么操作
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    /// 控制拖拽等操作
    Qt::DropActions supportedDropActions() const override;
    QStringList mimeTypes() const override;
    /// mime格式将可以存储整个树状结构 以字符串形式;
    /// mimedata格式:0|Group1|Group|UndefinedUUID|
    /// 首位代表层级; 层级1如果直接在层级0下,就说明是0的子节点;
    /// 所有批量操作TreeNode,都用这个形式;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parentNodeIndex) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parentNodeIndex) override;
public:
    ///  获取某个对象; 如果输入空index,就返回root
    TreeNode *getNode(const QModelIndex &index) const;
    /// \brief getIndex:获取某个节点的QtModelIndex; column输入0
    /// \param node 要获取的节点的指针
    QModelIndex getIndex(const TreeNode* node) const;
    QModelIndex getIndex(const UUID  uuid) const;

    /// \brief getAllChildNodes 获取所有子节点
    ///
    std::vector < TreeNode * > getAllChildNodes(const QModelIndex &nodeIndex) const;
    std::vector < QModelIndex > getAllChildIndexs(const QModelIndex &nodeIndex) const;
    /// \brief getClosedChildNodes 只获取下一层子节点
    /// \param nodeIndex
    std::vector < TreeNode * > getClosedChildNodes(const QModelIndex &nodeIndex) const;
    std::vector < QModelIndex > getClosedChildIndexs(const QModelIndex &nodeIndex) const;

    void setNodeProperty(const QModelIndex &nodeIndex, const TreeNodePropertyIndex propertyIndex, const QVariant &value);
    QVariant nodeProperty(const QModelIndex &nodeIndex, const TreeNodePropertyIndex propertyIndex);

    /// 外部强制视图刷新(暂时设置只刷新layer的选中以及visible)
    void update();
    void setupExemplarModelData();
    void setupDefaultModelData();

    // ///
    // /// 保存树结构到 JSON 文件/从文件加载
    // bool saveTreeToJson(const QString &filePath);
    // bool loadTreeFromJson(const QString &filePath);
    // TreeNode *deserializeTreeNode(const QJsonObject &obj);
    // QJsonObject serializeTreeNode(TreeNode *node);
    // void fillTreeNodeFromJson(TreeNode *node, const QJsonObject &obj);

private:
    void setupModelData(const QList < QStringView > &lines);
    void serializeNodeToStream(TreeNode *item, QDataStream &stream, int currentLevel) const;

    std::shared_ptr < TreeNode > m_rootItem; // 整个model的信息都存在rootItem里; 现在暂时存了model名字
};

#endif // TREEVIEWMODEL_H

