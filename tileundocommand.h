#ifndef TILEUNDOCOMMAND_H
#define TILEUNDOCOMMAND_H

#include <QUndoCommand>
#include <QSharedPointer>
#include <QModelIndex>
#include <QRect>

class TilePattern;
class MapModel;

class EmplaceCommand : public QUndoCommand {
public:
    EmplaceCommand(MapModel *model, QSharedPointer<TilePattern> pattern, const QRect &rect, int role, QUndoCommand *parent = nullptr);
    ~EmplaceCommand();

    void undo() override;
    void redo() override;

private:
    MapModel *m_model;
    QRect m_rect;
    int m_role;

    QSharedPointer<TilePattern> m_old;
    QSharedPointer<TilePattern> m_new;
};

class EmplaceRectCommand : public QUndoCommand {
public:
    EmplaceRectCommand(MapModel *model, QSharedPointer<TilePattern> pattern, const QModelIndexList &indexes, int role, QUndoCommand *parent = nullptr);
    ~EmplaceRectCommand();

    void undo() override;
    void redo() override;

private:
    MapModel *m_model;
    QModelIndexList m_indexes;
    int m_role;

    QSharedPointer<TilePattern> m_old;
    QSharedPointer<TilePattern> m_new;
};

class EmplaceFillCommand : public QUndoCommand {
public:
    EmplaceFillCommand(MapModel *model, QSharedPointer<TilePattern> pattern, const QModelIndexList &indexes, int role, QUndoCommand *parent = nullptr);
    ~EmplaceFillCommand();

    void undo() override;
    void redo() override;

private:
    MapModel *m_model;
    QModelIndexList m_indexes;
    int m_role;

    QSharedPointer<TilePattern> m_old;
    QSharedPointer<TilePattern> m_new;
};

#endif // TILEUNDOCOMMAND_H
