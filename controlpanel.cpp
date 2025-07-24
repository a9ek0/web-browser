#include "controlpanel.h"
#include "ui_controlpanel.h"

ControlPanel::ControlPanel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ControlPanel)
{
    ui->setupUi(this);

    connect(ui->addressBar, &QLineEdit::returnPressed, this, [=]{
        emit urlSubmited(ui->addressBar->text());
    });

    connect(ui->backButton, &QPushButton::clicked, this, &ControlPanel::backRequested);
    connect(ui->forwardButton, &QPushButton::clicked, this, &ControlPanel::forwardRequested);
    connect(ui->reloadButton, &QPushButton::clicked, this, &ControlPanel::reloadRequested);

}

ControlPanel::~ControlPanel()
{
    delete ui;
}

void ControlPanel::setUrl(const QUrl &url)
{
    ui->addressBar->setText(url.toString());
}
