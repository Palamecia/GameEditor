#ifndef MAPDELEGATE_H
#define MAPDELEGATE_H

#include <QStyledItemDelegate>

class MapDelegate : public QStyledItemDelegate {
public:
    explicit MapDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // MAPDELEGATE_H
