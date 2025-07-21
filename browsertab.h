#ifndef BROWSERTAB_H
#define BROWSERTAB_H

#include <QWidget>

namespace Ui {
class BrowserTab;
}

class BrowserTab : public QWidget
{
    Q_OBJECT

public:
    explicit BrowserTab(QWidget *parent = nullptr);
    ~BrowserTab();

private:
    Ui::BrowserTab *ui;
};

#endif // BROWSERTAB_H
