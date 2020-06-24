#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "chipsetdockwidget.h"
#include "tileundocommand.h"
#include "tilepattern.h"
#include "tilehelper.h"
#include "mapdelegate.h"
#include "mapmodel.h"

#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_chipsetDock(new ChipsetDockWidget(this)),
    m_emplaceActionGroup(this),
    m_layerActionGroup(this),
    m_editing(false) {
    m_ui->setupUi(this);
    m_ui->map->setItemDelegate(new MapDelegate(this));

    m_emplaceActionGroup.addAction(m_ui->actionEmplace);
    m_emplaceActionGroup.addAction(m_ui->actionEmplaceRect);
    m_emplaceActionGroup.addAction(m_ui->actionEmplaceFill);
    m_ui->actionEmplace->setChecked(true);

    m_layerActionGroup.addAction(m_ui->actionBackground);
    m_layerActionGroup.addAction(m_ui->actionForeground);
    m_ui->actionBackground->setChecked(true);

    connect(m_ui->actionUndo, &QAction::triggered, &m_undoStack, &QUndoStack::undo);
    connect(m_ui->actionRedo, &QAction::triggered, &m_undoStack, &QUndoStack::redo);
    connect(&m_undoStack, &QUndoStack::canUndoChanged, m_ui->actionUndo, &QAction::setEnabled);
    connect(&m_undoStack, &QUndoStack::canRedoChanged, m_ui->actionRedo, &QAction::setEnabled);
    m_ui->actionUndo->setEnabled(m_undoStack.canUndo());
    m_ui->actionRedo->setEnabled(m_undoStack.canRedo());

    addDockWidget(Qt::LeftDockWidgetArea, m_chipsetDock);
    connect(m_chipsetDock, &ChipsetDockWidget::tilePatternChanged, this, &MainWindow::updatePattern);

    m_model.reset(new MapModel(0));
    m_ui->map->setModel(m_model.data());
    connect(m_ui->map->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::editSelected);
    m_ui->map->viewport()->installEventFilter(this);
}

MainWindow::~MainWindow() {

}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {

    if (watched == m_ui->map->viewport()) {
        switch (event->type()) {
        case QEvent::MouseButtonRelease:
            m_ui->map->clearSelection();
            m_editing = false;
            break;

        default:
            break;
        }
    }

    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::updatePattern(TilePattern *pattern) {
    m_pattern.reset(pattern);
}

void MainWindow::editSelected() {
    if (QItemSelectionModel *selectionModel = m_ui->map->selectionModel()) {
        if (selectionModel->hasSelection()) {

            QRect rect = TileHelper::selectionToRect(selectionModel->selection().indexes());

            if (m_editing) {
                m_undoStack.undo();
            }

            if (m_ui->actionEmplace->isChecked()) {
                m_undoStack.push(new EmplaceCommand(m_model.data(), m_pattern, rect, layerRole()));
                m_ui->map->clearSelection();
                m_editing = true;
            }
            else if (m_ui->actionEmplaceRect->isChecked()) {
                m_undoStack.push(new EmplaceRectCommand(m_model.data(), m_pattern, selectionModel->selection().indexes(), layerRole()));
                m_editing = true;
            }
            else {
                QModelIndexList indexes = TileHelper::fillIndexes(m_model->index(rect.top(), rect.left()), layerRole());
                m_undoStack.push(new EmplaceFillCommand(m_model.data(), m_pattern, indexes, layerRole()));
                m_ui->map->clearSelection();
                m_editing = true;
            }
        }
    }
}

int MainWindow::layerRole() const {

    if (m_ui->actionBackground->isChecked()) {
        return Qt::BackgroundRole;
    }

    if (m_ui->actionForeground->isChecked()) {
        return Qt::ForegroundRole;
    }

    return Qt::ForegroundRole;
}
