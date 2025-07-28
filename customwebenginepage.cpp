#include "customwebenginepage.h"
#include "tabwidget.h"

CustomWebEnginePage::CustomWebEnginePage(TabWidget* tabWidget, QObject *parent)
    : m_tabWidget(tabWidget), QWebEnginePage{parent}
{}

QWebEnginePage *CustomWebEnginePage::createWindow(WebWindowType type) {
    auto newTab = m_tabWidget->addNewTab();
    return newTab->getWebView()->page();
}
