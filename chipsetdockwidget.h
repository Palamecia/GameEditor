#ifndef CHIPSETDOCKWIDGET_H
#define CHIPSETDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
class ChipsetDockWidget;
}

class QItemSelection;
class ChipsetModel;
class TilePattern;

class ChipsetDockWidget : public QDockWidget {
    Q_OBJECT
public:
    explicit ChipsetDockWidget(QWidget *parent = nullptr);
    ~ChipsetDockWidget();

signals:
    void tilePatternChanged(TilePattern *pattern);

private slots:
    void updateSelection();

private:
    QScopedPointer<Ui::ChipsetDockWidget> m_ui;
    QScopedPointer<ChipsetModel> m_model;
};

#endif // CHIPSETDOCKWIDGET_H
