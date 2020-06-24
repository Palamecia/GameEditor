#include "chipsetmodel.h"
#include "tilehelper.h"
#include "project.h"

#include <QDir>

ChipsetModel::ChipsetModel(uint16_t id, QObject *parent) :
    QAbstractTableModel(parent) {
    QDir projectDir(Project::instance().getPath());
    m_sprite.load(projectDir.filePath("Chipset/main.png"));
}

int ChipsetModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return 80;
}

int ChipsetModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return TileHelper::ChipsetColumnCount;
}

QVariant ChipsetModel::data(const QModelIndex &index, int role) const {

    if (role == Qt::DisplayRole) {
        return getId(index);
    }

    return QVariant();
}

uint16_t ChipsetModel::getId(const QModelIndex &index) const {
    return index.row() * columnCount() + index.column();
}

QPixmap ChipsetModel::getTile(uint16_t id) const {
    return TileHelper::tileFromId(m_sprite, id);
}
