#include "tileundocommand.h"
#include "tilepattern.h"
#include "tilehelper.h"
#include "mapmodel.h"

EmplaceCommand::EmplaceCommand(MapModel *model, QSharedPointer<TilePattern> pattern, const QRect &rect, int role, QUndoCommand *parent) :
    QUndoCommand(parent),
    m_model(model),
    m_rect(rect),
    m_role(role),
    m_old(new AreaPattern(model, QRect(rect.left(), rect.top(), pattern->columnCount(), pattern->rowCount()), role)),
    m_new(pattern) {

}

EmplaceCommand::~EmplaceCommand() {

}

void EmplaceCommand::undo() {
    m_model->setTile(m_model->index(m_rect.top(), m_rect.left()), m_old.data(), m_role);
}

void EmplaceCommand::redo() {
    m_model->setTile(m_model->index(m_rect.top(), m_rect.left()), m_new.data(), m_role);
}

EmplaceRectCommand::EmplaceRectCommand(MapModel *model, QSharedPointer<TilePattern> pattern, const QModelIndexList &indexes, int role, QUndoCommand *parent) :
    QUndoCommand(parent),
    m_model(model),
    m_indexes(indexes),
    m_role(role),
    m_old(new AreaPattern(model, TileHelper::selectionToRect(indexes), role)),
    m_new(pattern) {

}

EmplaceRectCommand::~EmplaceRectCommand() {

}

void EmplaceRectCommand::undo() {
    m_model->setTile(m_indexes, m_old.data(), m_role);
}

void EmplaceRectCommand::redo() {
    m_model->setTile(m_indexes, m_new.data(), m_role);
}


EmplaceFillCommand::EmplaceFillCommand(MapModel *model, QSharedPointer<TilePattern> pattern, const QModelIndexList &indexes, int role, QUndoCommand *parent) :
    QUndoCommand(parent),
    m_model(model),
    m_indexes(indexes),
    m_role(role),
    m_old(new AreaPattern(model, TileHelper::selectionToRect(indexes), role)),
    m_new(pattern) {

}

EmplaceFillCommand::~EmplaceFillCommand() {

}

void EmplaceFillCommand::undo() {
    m_model->setTile(m_indexes, m_old.data(), m_role);
}

void EmplaceFillCommand::redo() {
    m_model->setTile(m_indexes, m_new.data(), m_role);
}
