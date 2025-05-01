#ifndef COLORDELEGATE_H
#define COLORDELEGATE_H

#include <QColor>
#include <QStyledItemDelegate>

class ColorDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    void paint(QPainter *painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &,
                          const QModelIndex &) const override;
    void setEditorData(QWidget *, const QModelIndex &) const override {}
    void setModelData(QWidget *, QAbstractItemModel *, const QModelIndex &) const override {}

    bool editorEvent(QEvent *event,
                     QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) override;
};

#endif // COLORDELEGATE_H
