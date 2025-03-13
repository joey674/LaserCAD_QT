#ifndef ITEMTREEWIDGET_H
#define ITEMTREEWIDGET_H

#include <QTreeWidget>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QTreeWidgetItem>
#include <QPainter>
#include <QPaintEvent>


class ItemTreeWidget : public QTreeWidget
{
    Q_OBJECT

public:
    explicit ItemTreeWidget(QWidget *parent = nullptr)
    {
        setContextMenuPolicy(Qt::CustomContextMenu);
        connect(this, &QTreeWidget::customContextMenuRequested, this, &ItemTreeWidget::onShowContextMenu);
        connect(this, &QTreeWidget::itemClicked, this,&ItemTreeWidget::onItemClicked);
    };
private:
    QRect dropIndicatorRect;
    enum DropEventType {
        OnItem,
        AboveItem,
        BelowItem
    };
    DropEventType getDropEventType(QDropEvent *event);
    int getItemLevel(QTreeWidgetItem *item);
    void removeParent(QTreeWidgetItem *childItem);

private slots:
    void onShowContextMenu(const QPoint &pos);
    void onItemClicked(QTreeWidgetItem *item, int column);
protected:
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
};


#endif // ITEMTREEWIDGET_H
