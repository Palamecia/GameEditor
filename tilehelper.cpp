#include "tilehelper.h"

QRect TileHelper::selectionToRect(const QModelIndexList &selected) {

    QRect rect;

    for (const QModelIndex &index : selected) {
        if (rect.isValid()) {
            rect.setTop(qMin(index.row(), rect.top()));
            rect.setLeft(qMin(index.column(), rect.left()));
            rect.setBottom(qMax(index.row(), rect.bottom()));
            rect.setRight(qMax(index.column(), rect.right()));
        }
        else {
            rect = QRect(index.column(), index.row(), 1, 1);
        }
    }

    return rect;
}

QPixmap TileHelper::tileFromId(const QPixmap &chipset, uint16_t id) {

    int row = id / TileHelper::ChipsetColumnCount;
    int column = id % TileHelper::ChipsetColumnCount;

    column += row / TileHelper::ChipsetRowCount * TileHelper::ChipsetColumnCount;
    row = row % TileHelper::ChipsetRowCount;

    return chipset.copy(QRect(column * 16, row * 16, 16, 16));
}

static void fillRecursiveHelper(QModelIndexList &indexes, const QModelIndex &origin, uint16_t value, int role);
static void fillRecursiveIndexHelper(QModelIndexList &indexes, const QModelIndex &index, uint16_t value, int role);

void fillRecursiveHelper(QModelIndexList &indexes, const QModelIndex &origin, uint16_t value, int role) {

    const QAbstractItemModel *model = origin.model();

    fillRecursiveIndexHelper(indexes, model->index(origin.row() - 1, origin.column()), value, role);
    fillRecursiveIndexHelper(indexes, model->index(origin.row() + 1, origin.column()), value, role);
    fillRecursiveIndexHelper(indexes, model->index(origin.row(), origin.column() - 1), value, role);
    fillRecursiveIndexHelper(indexes, model->index(origin.row(), origin.column() + 1), value, role);
}

void fillRecursiveIndexHelper(QModelIndexList &indexes, const QModelIndex &index, uint16_t value, int role) {
    if (index.isValid() && !indexes.contains(index) && (value == index.data(role).toInt())) {
        indexes.append(index);
        fillRecursiveHelper(indexes, index, value, role);
    }
}

QModelIndexList TileHelper::fillIndexes(const QModelIndex &origin, int role) {

    QModelIndexList indexes;
    uint16_t value = origin.data(role).toInt();
    fillRecursiveIndexHelper(indexes, origin, value, role);
    return indexes;
}
