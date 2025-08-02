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

        connect(historyEntry, &HistoryEntryWidget::entryDeleted, this, [=](const HistoryEntryWidget *historyEntryWidget){
            for (int i = 0; i < ui->historyList->count(); ++i) {
                auto* item = ui->historyList->item(i);
                if (ui->historyList->itemWidget(item) == historyEntryWidget) {
                    delete ui->historyList->takeItem(i);
                    break;
                }
            }
        });
    }


}

HistoryWidget::~HistoryWidget()
{
    delete ui;
}
