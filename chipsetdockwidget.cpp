#include "chipsetdockwidget.h"
#include "ui_chipsetdockwidget.h"

#include "chipsetdelegate.h"
#include "chipsetmodel.h"
#include "tilepattern.h"

ChipsetDockWidget::ChipsetDockWidget(QWidget *parent) :
    QDockWidget(parent),
    m_ui(new Ui::ChipsetDockWidget) {
    m_ui->setupUi(this);
    m_ui->chipset->setItemDelegate(new ChipsetDelegate(this));

    m_model.reset(new ChipsetModel(0));
    m_ui->chipset->setModel(m_model.data());
    connect(m_ui->chipset->selectionModel(), &QItemSelectionModel::selectionChanged, this, &ChipsetDockWidget::updateSelection);
    m_ui->chipset->selectionModel()->select(m_model->index(0, 0), QItemSelectionModel::SelectCurrent);
}

ChipsetDockWidget::~ChipsetDockWidget() {

}

void ChipsetDockWidget::updateSelection() {
    if (QItemSelectionModel *selectionModel = m_ui->chipset->selectionModel()) {
        if (selectionModel->hasSelection()) {
            emit tilePatternChanged(new RangePattern(m_model.data(), selectionModel->selection().indexes()));
        }
        else {
            m_ui->chipset->selectionModel()->select(m_model->index(0, 0), QItemSelectionModel::SelectCurrent);
        }
    }
}
