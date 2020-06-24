#ifndef TILEPATTERN_H
#define TILEPATTERN_H

#include <QModelIndex>
#include <QRect>

class ChipsetModel;
class MapModel;

class TilePattern {
public:
    TilePattern();

    virtual int rowCount() const = 0;
    virtual int columnCount() const = 0;

    virtual uint16_t getIdAt(const QModelIndex &origin, const QModelIndex &index) const = 0;
};

class RangePattern : public TilePattern {
public:
    RangePattern(ChipsetModel *model, const QModelIndexList &selected);

    int rowCount() const override;
    int columnCount() const override;

    uint16_t getIdAt(const QModelIndex &origin, const QModelIndex &index) const override;

private:
    ChipsetModel *m_model;
    QRect m_rect;
};

class AreaPattern : public TilePattern {
public:
    AreaPattern(MapModel *model, const QRect &rect, int role);

    int rowCount() const override;
    int columnCount() const override;

    uint16_t getIdAt(const QModelIndex &origin, const QModelIndex &index) const override;

private:
    QRect m_rect;
    QList<uint16_t> m_data;
};

#endif // TILEPATTERN_H
