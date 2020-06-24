#ifndef MAPMODEL_H
#define MAPMODEL_H

#include <QAbstractTableModel>
#include <QPixmap>

class TilePattern;

class MapModel : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit MapModel(uint16_t id, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QPixmap getTile(uint16_t id) const;
    void setTile(const QModelIndex &origin, const TilePattern *pattern, int role);
    void setTile(const QModelIndexList &selected, const TilePattern *pattern, int role);

private:
    QPixmap m_sprite;

    /// \todo use shared map struct
    int m_height;
    int m_width;
    QVector<uint16_t> m_background;
    QVector<uint16_t> m_foreground;
};

#endif // MAPMODEL_H
