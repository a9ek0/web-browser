#include "browsertab.h"
#include "ui_browsertab.h"

BrowserTab::BrowserTab(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BrowserTab)
{
    ui->setupUi(this);
}

BrowserTab::~BrowserTab()
{
    delete ui;
}
