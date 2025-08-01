#ifndef BROWSERTAB_H
#define BROWSERTAB_H

#include <QWidget>
#include <QWebEngineView>
#include <QWebEngineHistory>
#include "controlpanel.h"
#include "customwebenginepage.h"
#include "historywidget.h"

namespace Ui {
class BrowserTab;
}

class BrowserTab : public QWidget
{
    Q_OBJECT

public:
    explicit BrowserTab(QWidget *parent = nullptr);
    ~BrowserTab();

    QWebEngineView *getWebView() const;
    void setWebView(QWebEngineView *newWebView);

    ControlPanel *getControlPanel() const;
    void setControlPanel(ControlPanel *newControlPanel);

signals:
    void urlEntered(const QString& url);
    void urlChanged(const QUrl &url);
    void titleChanged(BrowserTab*, const QString&);
    void navigationStateChanged(bool canGoBack, bool canGoForward);
    void loadStarted();
    void loadFinished(const QString &url, const QString &title);
    void faviconChanged(const QIcon &favicon);
    void addSpecTab(QWidget *widget, const QString &title);

private:
    Ui::BrowserTab *ui;
    QWebEngineView *webView;
    ControlPanel   *controlPanel;
};

#endif // BROWSERTAB_H
