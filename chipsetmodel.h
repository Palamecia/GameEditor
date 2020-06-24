#ifndef CHIPSETMODEL_H
#define CHIPSETMODEL_H

#include <QAbstractTableModel>
#include <QPixmap>

class ChipsetModel : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit ChipsetModel(uint16_t id, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    uint16_t getId(const QModelIndex &index) const;
    QPixmap getTile(uint16_t id) const;

private:
    QPixmap m_sprite;
};

#endif // CHIPSETMODEL_H
