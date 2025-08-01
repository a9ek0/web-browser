#include "browsertab.h"
#include "ui_browsertab.h"
#include "tabwidget.h"

BrowserTab::BrowserTab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BrowserTab)
{
    ui->setupUi(this);

    auto webPage = new CustomWebEnginePage(qobject_cast<TabWidget*>(parentWidget()), this);
    webView = new QWebEngineView(this);

    webView->setPage(webPage);
    webView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    if (auto webViewLayout = findChild<QVBoxLayout*>("webViewLayout")) {
        webViewLayout->addWidget(webView);
    } else {
        qWarning() << "WebView layout not found!";
        auto layout = new QVBoxLayout(this);
        layout->addWidget(webView);
    }

    controlPanel = new ControlPanel(this);
    controlPanel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    if (auto panelLayout = findChild<QVBoxLayout*>("controlPanelLayout")) {
        panelLayout->addWidget(controlPanel);
    } else {
        qWarning() << "Control panel layout not found!";
        if (auto mainLayout = qobject_cast<QVBoxLayout*>(layout())) {
            mainLayout->insertWidget(0, controlPanel);
        }
    }

    connect(controlPanel, &ControlPanel::backRequested, webView, &QWebEngineView::back);
    connect(controlPanel, &ControlPanel::forwardRequested, webView, &QWebEngineView::forward);
    connect(controlPanel, &ControlPanel::reloadRequested, webView, &QWebEngineView::reload);
    connect(controlPanel, &ControlPanel::openHistoryRequested, this, [=]() {
        auto* history = new HistoryWidget;
        emit addSpecTab(history, "History");
    });
    connect(webView, &QWebEngineView::urlChanged, this, [=](const QUrl& url){
        emit urlChanged(url);
        emit navigationStateChanged(webView->history()->canGoBack(), webView->history()->canGoForward());
    });
    connect(webView, &QWebEngineView::titleChanged, this, [=](const QString& title){
        emit titleChanged(this, title);
    });
    connect(webView, &QWebEngineView::loadStarted, this, [=]() {
        emit loadStarted();
    });
    connect(webView, &QWebEngineView::loadFinished, this, [=](bool ok) {
        emit loadFinished(webView->url().toString(), webView->title());
    });
    connect(webView, &QWebEngineView::iconChanged, this, [=](const QIcon &icon){
        emit faviconChanged(icon);
    });

    connect(webView, &QWebEngineView::loadFinished, [](bool ok) {
        if (!ok) qWarning() << "Page load failed";
    });

    webView->setUrl(QUrl("qrc:/html/resources/html/newtab.html"));

}

BrowserTab::~BrowserTab()
{
    delete ui;
}

QWebEngineView *BrowserTab::getWebView() const
{
    return webView;
}

void BrowserTab::setWebView(QWebEngineView *newWebView)
{
    webView = newWebView;
}

ControlPanel *BrowserTab::getControlPanel() const
{
    return controlPanel;
}

void BrowserTab::setControlPanel(ControlPanel *newControlPanel)
{
    controlPanel = newControlPanel;
}
