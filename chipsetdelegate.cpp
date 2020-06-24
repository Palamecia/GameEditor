#include "chipsetdelegate.h"
#include "chipsetmodel.h"

#include <QPainter>

ChipsetDelegate::ChipsetDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {

}

void ChipsetDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {

    if (const ChipsetModel *model = dynamic_cast<const ChipsetModel *>(index.model())) {

        painter->drawPixmap(option.rect, model->getTile(index.data().toInt()));

        if (option.state & QStyle::State_Selected) {
            painter->save();
            painter->setPen(Qt::NoPen);
            painter->setBrush(QColor("#5582B1FF"));
            painter->drawRect(option.rect);
            painter->restore();
        }
    }
}
