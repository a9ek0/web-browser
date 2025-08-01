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

private:
    Ui::HistoryEntryWidget *ui;
};

#endif // HISTORYENTRYWIDGET_H
