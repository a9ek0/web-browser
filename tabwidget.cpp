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
        auto newTab = new BrowserTab(this);
        int i = addTab(newTab, "New Tab");
        setCurrentIndex(i);
    });

    setCornerWidget(btn);

    auto firstTab = new BrowserTab(this);
    addTab(firstTab, "New Tab");
}
