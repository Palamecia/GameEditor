#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QActionGroup>
#include <QUndoStack>

namespace Ui {
class MainWindow;
}

class QItemSelection;
class ChipsetDockWidget;
class TilePattern;
class MapModel;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void updatePattern(TilePattern *pattern);
    void editSelected();

private:
    int layerRole() const;

    QScopedPointer<Ui::MainWindow> m_ui;
    ChipsetDockWidget *m_chipsetDock;
    QScopedPointer<MapModel> m_model;

    QActionGroup m_emplaceActionGroup;
    QActionGroup m_layerActionGroup;
    QSharedPointer<TilePattern> m_pattern;
    QUndoStack m_undoStack;
    bool m_editing;
};

#endif // MAINWINDOW_H
