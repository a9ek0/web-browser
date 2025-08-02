#include "historyentrywidget.h"
#include "ui_historyentrywidget.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMenu>

HistoryEntryWidget::HistoryEntryWidget(const HistoryEntry &entry, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HistoryEntryWidget)
{
    ui->setupUi(this);

    this->entry.timestamp = entry.timestamp;
    this->entry.title = entry.title;
    this->entry.timestamp = entry.timestamp;

    QString domain = QUrl(entry.url).host();
    QUrl faviconUrl(QString("https://www.google.com/s2/favicons?domain=%1&sz=32").arg(domain));

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkRequest request(faviconUrl);

    connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply* reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QPixmap pixmap;
            pixmap.loadFromData(reply->readAll());
            ui->iconLabel->setPixmap(pixmap.scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        } else {
            QPixmap pixmap(":/icons/resources/icons/default.png");
            ui->iconLabel->setPixmap(pixmap.scaled(16, 16, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        reply->deleteLater();
        manager->deleteLater();
    });

    manager->get(request);

    ui->timeLineEdit->setText(entry.timestamp.time().toString());
    ui->titleLineEdit->setText(entry.title);
    ui->urlLineEdit->setText(HistoryManager::simplifyUrl(entry.url));

    auto *menu = new QMenu(ui->menuButton);
    auto removeEntryAction = new QAction("Remove", menu);
    menu->addAction(removeEntryAction);
    ui->menuButton->setMenu(menu);

    connect(removeEntryAction, &QAction::triggered, this, [=](){
        HistoryManager::instance().removeEntry(this->entry.timestamp);
        emit entryDeleted(this);
    });
}

HistoryEntryWidget::~HistoryEntryWidget()
{
    delete ui;
}
