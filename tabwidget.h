#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QPushButton>
#include <QDateTime>
#include "browsertab.h"
#include "controlpanel.h"
#include "historymanager.h"

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:

    explicit TabWidget(QWidget *parent = nullptr);

    BrowserTab* addNewTab();

signals:
    void urlRequested(BrowserTab *tab, const QString &url);

};

#endif // TABWIDGET_H
