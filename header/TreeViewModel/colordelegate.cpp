// ColorDelegate.cpp
#include "colordelegate.h"
#include <QApplication>
#include <QColorDialog>
#include <QDebug>
#include <QPainter>
#include "logger.h"
#include "treemodel.h"

void ColorDelegate::paint(QPainter *painter,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{
    auto model = qobject_cast<const TreeModel *>(index.model());
    if (!model) {
        WARN_MSG("");
        return;
    }
    TreeNode *node = model->getNode(index);
    if (!node) {
        WARN_MSG("");
        return;
    }
    QString type = node->property(TreeNodePropertyIndex::Type).toString();
    if (type != "Layer") { // 只有layer显示颜色框
        return;
    }

    QVariant value = index.model()->data(index, Qt::BackgroundRole);
    QColor color = value.value<QColor>();

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    QRect rect = option.rect.adjusted(4, 4, -4, -4);
    painter->setBrush(color);
    painter->setPen(Qt::black);
    painter->drawRect(rect);

    painter->restore();
}

QWidget *ColorDelegate::createEditor(QWidget *parent,
                                     const QStyleOptionViewItem &,
                                     const QModelIndex &index) const
{
    QVariant value = index.model()->data(index, Qt::BackgroundRole);
    QColor currentColor = value.value<QColor>();

    QColor selectedColor = QColorDialog::getColor(currentColor, parent, "select color");
    if (selectedColor.isValid()) {
        const_cast<QAbstractItemModel *>(index.model())
            ->setData(index, selectedColor, Qt::BackgroundRole);
    }

    return nullptr;
}

bool ColorDelegate::editorEvent(QEvent *event,
                                QAbstractItemModel *model,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index)
{
    if (!(index.flags() & Qt::ItemIsEditable)) {
        return false;
    }
    if (event->type() == QEvent::MouseButtonRelease) {
        QWidget *editor = createEditor(nullptr, option, index);
        Q_UNUSED(editor);
        return true;
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
