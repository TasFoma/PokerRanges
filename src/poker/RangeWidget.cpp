#include "RangeWidget.h"
#include "RangeItemDelegate.h"
#include "RangeTableModel.h"

#include <QHeaderView>
#include <QVBoxLayout>

RangeWidget::RangeWidget(QWidget *parent)
    : QWidget(parent), tableView_(new QTableView(this))
    , model_(new RangeTableModel(this)),
      delegate_(new RangeItemDelegate(this)),
      generateButton_(new QPushButton("Generate New Range", this)) {
    auto *layout = new QVBoxLayout(this);

    setMinimumSize(1000, 800);

    tableView_->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView_->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView_->horizontalHeader()->show();
    tableView_->verticalHeader()->show();
    tableView_->setShowGrid(false);
    tableView_->setFrameShape(QFrame::NoFrame);
    tableView_->setStyleSheet("QTableView { background-color: black; }"
                              "QHeaderView::section { background-color: white; color: darkgray; }");

    tableView_->setModel(model_);
    tableView_->setItemDelegate(new RangeItemDelegate(this));

    generateButton_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(generateButton_, &QPushButton::clicked, this, &RangeWidget::onGenerateClicked);

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(generateButton_);
    buttonLayout->addStretch();

    layout->addWidget(tableView_, 1); // give table the expanding stretch
    layout->addLayout(buttonLayout, 0);

    setWindowTitle("Poker Range Visualizer");
    adjustSize();
}
void RangeWidget::onGenerateClicked() { model_->generateNewRange(); }
