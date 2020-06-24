#include "mapmodel.h"
#include "tilepattern.h"
#include "tilehelper.h"
#include "project.h"

#include <QDir>

MapModel::MapModel(uint16_t id, QObject *parent) :
    QAbstractTableModel(parent),
    m_height(15),
    m_width(20) {
    QDir projectDir(Project::instance().getPath());
    m_sprite.load(projectDir.filePath("Chipset/main.png"));
    for (int row = 0; row < m_height; ++row) {
        for (int column = 0; column < m_width; ++column) {
            m_background.append(100);
            m_foreground.append(336);
        }
    }
}

int MapModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_height;
}

int MapModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_width;
}

QVariant MapModel::data(const QModelIndex &index, int role) const {

    switch (role) {
    case Qt::BackgroundRole:
        return m_background.at(index.column() + index.row() * m_width);

    case Qt::ForegroundRole:
        return m_foreground.at(index.column() + index.row() * m_width);

    default:
        break;
    }

    return QVariant();
}

QPixmap MapModel::getTile(uint16_t id) const {
    return TileHelper::tileFromId(m_sprite, id);
}

void MapModel::setTile(const QModelIndex &origin, const TilePattern *pattern, int role) {

    QModelIndex last = index(origin.row() + pattern->rowCount(), origin.column() + pattern->columnCount());

    switch (role) {
    case Qt::BackgroundRole:
        for (int row = 0; row < pattern->rowCount(); ++row) {
            for (int column = 0; column < pattern->columnCount(); ++column) {
                QModelIndex index = this->index(row + origin.row(), column + origin.column());
                m_background[index.column() + index.row() * m_width] = pattern->getIdAt(origin, index);
            }
        }
        emit dataChanged(origin, last);
        break;

    case Qt::ForegroundRole:
        for (int row = 0; row < pattern->rowCount(); ++row) {
            for (int column = 0; column < pattern->columnCount(); ++column) {
                QModelIndex index = this->index(row + origin.row(), column + origin.column());
                m_foreground[index.column() + index.row() * m_width] = pattern->getIdAt(origin, index);
            }
        }
        emit dataChanged(origin, last);
        break;

    default:
        break;
    }
}

void MapModel::setTile(const QModelIndexList &selected, const TilePattern *pattern, int role) {

    QRect rect = TileHelper::selectionToRect(selected);
    QModelIndex origin = index(rect.top(), rect.left());
    QModelIndex last = index(rect.bottom(), rect.right());

    switch (role) {
    case Qt::BackgroundRole:
        for (const QModelIndex &index : selected) {
            m_background[index.column() + index.row() * m_width] = pattern->getIdAt(origin, index);
        }
        if (!selected.isEmpty()) {
            emit dataChanged(origin, last);
        }
        break;

    case Qt::ForegroundRole:
        for (const QModelIndex &index : selected) {
            m_foreground[index.column() + index.row() * m_width] = pattern->getIdAt(origin, index);
        }
        if (!selected.isEmpty()) {
            emit dataChanged(origin, last);
        }
        break;

    default:
        break;
    }
}
