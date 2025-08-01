#include "controlpanel.h"
#include "ui_controlpanel.h"

ControlPanel::ControlPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ControlPanel)
{
    ui->setupUi(this);

// Вынести отдельно
    auto *menu = new QMenu(ui->menuButton);
    auto showHistoryAction = new QAction("История", menu);
    menu->addAction(showHistoryAction);
    ui->menuButton->setMenu(menu);
//

    ui->backButton->setEnabled(false);
    ui->forwardButton->setEnabled(false);

    connect(ui->addressBar, &QLineEdit::returnPressed, this, [=]{
        emit urlSubmited(ui->addressBar->text());
    });

    connect(ui->backButton, &QPushButton::clicked, this, &ControlPanel::backRequested);
    connect(ui->forwardButton, &QPushButton::clicked, this, &ControlPanel::forwardRequested);
    connect(ui->reloadButton, &QPushButton::clicked, this, &ControlPanel::reloadRequested);
    connect(showHistoryAction, &QAction::triggered, this, &ControlPanel::openHistoryRequested);

}

ControlPanel::~ControlPanel()
{
    delete ui;
}

void ControlPanel::setUrl(const QUrl &url)
{
    ui->addressBar->setText(url.toString());
}

void ControlPanel::setNavigationEnabled(bool canGoBack, bool canGoForward)
{
    ui->backButton->setEnabled(canGoBack);
    ui->forwardButton->setEnabled(canGoForward);
}
