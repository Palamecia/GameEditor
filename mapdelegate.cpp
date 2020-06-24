#include "mapdelegate.h"
#include "mapmodel.h"

#include <QPainter>

MapDelegate::MapDelegate(QObject *parent) :
    QStyledItemDelegate(parent) {

}

void MapDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (const MapModel *model = dynamic_cast<const MapModel *>(index.model())) {
        painter->drawPixmap(option.rect, model->getTile(index.data(Qt::BackgroundRole).toInt()));
        painter->drawPixmap(option.rect, model->getTile(index.data(Qt::ForegroundRole).toInt()));
    }
}
