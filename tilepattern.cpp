#include "tilepattern.h"
#include "chipsetmodel.h"
#include "mapmodel.h"
#include "tilehelper.h"

TilePattern::TilePattern() {

}

RangePattern::RangePattern(ChipsetModel *model, const QModelIndexList &selected) :
    m_model(model),
    m_rect(TileHelper::selectionToRect(selected)) {

}

int RangePattern::rowCount() const {
    return m_rect.height();
}

int RangePattern::columnCount() const {
    return m_rect.width();
}

uint16_t RangePattern::getIdAt(const QModelIndex &origin, const QModelIndex &index) const {

    int x = index.column() - origin.column();
    int y = index.row() - origin.row();

    int column = m_rect.x() + x % m_rect.width();
    int row = m_rect.y() + y % m_rect.height();

    return m_model->getId(m_model->index(row, column));
}

AreaPattern::AreaPattern(MapModel *model, const QRect &rect, int role) :
    m_rect(rect) {
    for (int row = 0; row < rect.height(); ++row) {
        for (int column = 0; column < rect.width(); ++column) {
            m_data.append(model->index(row + rect.top(), column + rect.left()).data(role).toInt());
        }
    }
}

int AreaPattern::rowCount() const {
    return m_rect.height();
}

int AreaPattern::columnCount() const {
    return m_rect.width();
}

uint16_t AreaPattern::getIdAt(const QModelIndex &origin, const QModelIndex &index) const {

    int x = index.column() - origin.column();
    int y = index.row() - origin.row();

    int column = x % m_rect.width();
    int row = y % m_rect.height();

    return m_data.value(column + row * m_rect.width());
}
