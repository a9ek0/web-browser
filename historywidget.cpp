#include "historywidget.h"
#include "ui_historywidget.h"

HistoryWidget::HistoryWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HistoryWidget)
{
    ui->setupUi(this);

    auto history = HistoryManager::instance().getEntries();
    for(const auto &entry : history)
    {
        auto *item = new QListWidgetItem(ui->historyList);
        auto *historyEntry = new HistoryEntryWidget(entry, ui->historyList);

        item->setSizeHint(historyEntry->sizeHint());
        ui->historyList->setItemWidget(item, historyEntry);
    }
}

HistoryWidget::~HistoryWidget()
{
    delete ui;
}
