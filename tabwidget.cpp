#include "tabwidget.h"

TabWidget::TabWidget(QWidget *parent)
    : QTabWidget(parent)
{
    setTabsClosable(true);

    connect(this, &QTabWidget::tabCloseRequested, this, [=](int index){
        QWidget *tab = widget(index);
        removeTab(index);
        delete tab;
    });

    auto btn = new QPushButton("+");
    btn->setFixedSize(20, 20);

    connect(btn, &QPushButton::clicked, this, [=](){
        addNewTab();
    });

    setCornerWidget(btn);

    addNewTab();
}

BrowserTab *TabWidget::addNewTab()
{
    auto newTab = new BrowserTab(this);

    connect(newTab, &BrowserTab::urlChanged, newTab->getControlPanel(), &ControlPanel::setUrl);
    connect(newTab, &BrowserTab::navigationStateChanged, newTab->getControlPanel(), &ControlPanel::setNavigationEnabled);
    connect(newTab->getControlPanel(), &ControlPanel::urlSubmited, this, [this, newTab](const QString& url) {
        emit urlRequested(newTab, url);
    });

    connect(newTab, &BrowserTab::titleChanged, this, [=](BrowserTab* sender, const QString& title) {
        int index = indexOf(sender);
        if (index != -1) {
            setTabText(index, title);
        }
    });

    connect(newTab, &BrowserTab::loadStarted, this, [=]() {
        int index = indexOf(newTab);
        if (index >= 0) {
            QIcon loadingIcon(":/icons/resources/icons/loading.png");
            setTabIcon(index, loadingIcon);
        }
    });

    connect(newTab, &BrowserTab::loadFinished, this, [=](const QString &url, const QString &title) {
        int index = indexOf(newTab);
        if (index >= 0) {
            QIcon defaultIcon(":/icons/resources/icons/default.png");
            setTabIcon(index, defaultIcon);
        }

        HistoryManager::instance().addEntry(url, title, QDateTime::currentDateTime());
    });

    connect(newTab, &BrowserTab::faviconChanged, this, [=](const QIcon &icon){
        int index = indexOf(newTab);
        if (index >= 0) {
            setTabIcon(index, icon.isNull() ? QIcon(":/icons/resources/icons/default.png") : icon);
        }
    });

    connect(newTab, &BrowserTab::addSpecTab, this, [=](QWidget *widget, const QString &title){
        int i = addTab(widget, title);
        setCurrentIndex(i);
    });

    int i = addTab(newTab, "NewTab");
    setCurrentIndex(i);
    return newTab;
}
