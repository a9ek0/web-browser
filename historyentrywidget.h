#ifndef HISTORYENTRYWIDGET_H
#define HISTORYENTRYWIDGET_H

#include <QWidget>
#include "historymanager.h"

namespace Ui {
class HistoryEntryWidget;
}

class HistoryEntryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryEntryWidget(const HistoryEntry &entry, QWidget *parent = nullptr);
    ~HistoryEntryWidget();

signals:
    void entryDeleted(const HistoryEntryWidget *historyEntryWidget);

private:
    Ui::HistoryEntryWidget *ui;
    HistoryEntry entry;
};

#endif // HISTORYENTRYWIDGET_H
