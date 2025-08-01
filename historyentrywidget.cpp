#include "historyentrywidget.h"
#include "ui_historyentrywidget.h"

HistoryEntryWidget::HistoryEntryWidget(const HistoryEntry &entry, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HistoryEntryWidget)
{
    ui->setupUi(this);

    ui->iconLabel;
    ui->timeLineEdit->setText(entry.timestamp.time().toString());
    ui->titleLineEdit->setText(entry.title);
    ui->urlLineEdit->setText(entry.url);
}

HistoryEntryWidget::~HistoryEntryWidget()
{
    delete ui;
}
