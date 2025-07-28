#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QString>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QStandardPaths>
#include <QDir>

struct HistoryEntry {
    QString url;
    QString title;
    QDateTime timestamp;
};

class HistoryManager
{
public:
    static HistoryManager& instance();
    void addEntry(const QString &url, const QString &title, const QDateTime &timeStamp);
    const QList<HistoryEntry>& getEntries() const;
    void save();
    void load();
    void clear();

private:
    HistoryManager();
    QList<HistoryEntry> history;
};

#endif // HISTORYMANAGER_H
