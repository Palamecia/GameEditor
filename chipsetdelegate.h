#ifndef CHIPSETDELEGATE_H
#define CHIPSETDELEGATE_H

#include <QStyledItemDelegate>

class ChipsetDelegate : public QStyledItemDelegate {
public:
    explicit ChipsetDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // CHIPSETDELEGATE_H
