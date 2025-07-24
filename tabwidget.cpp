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

    connect(newTab->getControlPanel(), &ControlPanel::urlSubmited, this, [this, newTab](const QString& url) {
        emit urlRequested(newTab, url);
    });

    connect(newTab, &BrowserTab::titleChanged, this, [=](BrowserTab* sender, const QString& title) {
        int index = indexOf(sender);
        if (index != -1) {
            setTabText(index, title);
        }
    });

    int i = addTab(newTab, "NewTab");
    setCurrentIndex(i);
    return newTab;
}
