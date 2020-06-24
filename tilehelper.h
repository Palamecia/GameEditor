#ifndef TILEHELPER_H
#define TILEHELPER_H

#include <QModelIndex>
#include <QPixmap>

namespace TileHelper {

static constexpr int ChipsetRowCount = 16;
static constexpr int ChipsetColumnCount = 6;

QRect selectionToRect(const QModelIndexList &selected);
QPixmap tileFromId(const QPixmap &chipset, uint16_t id);

QModelIndexList fillIndexes(const QModelIndex &origin, int role);

}

#endif // TILEHELPER_H
