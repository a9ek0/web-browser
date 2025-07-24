#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QWidget>

namespace Ui {
class ControlPanel;
}

class ControlPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ControlPanel(QWidget *parent = nullptr);
    ~ControlPanel();

signals:
    void urlSubmited(const QString& url);
    void backRequested();
    void forwardRequested();
    void reloadRequested();

public slots:
    void setUrl(const QUrl &url);

private:
    Ui::ControlPanel *ui;
};

#endif // CONTROLPANEL_H
