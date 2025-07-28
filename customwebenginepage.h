#ifndef CUSTOMWEBENGINEPAGE_H
#define CUSTOMWEBENGINEPAGE_H

#include <QObject>
#include <QWebEnginePage>

class TabWidget;

class CustomWebEnginePage : public QWebEnginePage
{
    Q_OBJECT
public:
    explicit CustomWebEnginePage(TabWidget* tabWidget, QObject *parent = nullptr);

protected:
    QWebEnginePage* createWindow(WebWindowType type) override;

private:
    TabWidget *m_tabWidget;
};

#endif // CUSTOMWEBENGINEPAGE_H
