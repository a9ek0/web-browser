#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qpushbutton.h>
#include <QTabBar>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    HistoryManager::instance().load();

    connect(ui->browserTabs, &TabWidget::urlRequested, this, &MainWindow::loadPage);
}

MainWindow::~MainWindow()
{
    HistoryManager::instance().save();
    delete ui;
}

void MainWindow::loadPage(BrowserTab *tab, const QString &url)
{
    qDebug() << "LOADPAGE";
    QUrl qurl = QUrl::fromUserInput(url);
    tab->getWebView()->load(qurl);
}
