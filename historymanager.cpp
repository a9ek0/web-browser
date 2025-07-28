#include "historymanager.h"

HistoryManager::HistoryManager() {}

HistoryManager &HistoryManager::instance()
{
    static HistoryManager instance;
    return instance;
}

void HistoryManager::addEntry(const QString &url, const QString &title, const QDateTime &timeStamp)
{
    const int maxEntries = 500;
    if (history.size() > maxEntries)
        history = history.mid(history.size() - maxEntries);

    history.append(HistoryEntry{url, title, timeStamp});
}

const QList<HistoryEntry> &HistoryManager::getEntries() const
{
    return history;
}

void HistoryManager::save()
{
    QJsonArray jsonArray;
    for(const HistoryEntry &entry : history)
    {
        QJsonObject obj;
        obj["url"] = entry.url;
        obj["title"] = entry.title;
        obj["timestamp"] = entry.timestamp.toString(Qt::ISODate);

        jsonArray.append(obj);
    };

    QJsonDocument doc(jsonArray);

    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);
    QFile file(path + "/history.json");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qWarning() << "Could not open history.json for writing";
        return;
    }

    file.write(doc.toJson());
    file.close();
}

void HistoryManager::load()
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);
    QFile file(path + "/history.json");
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray data = file.readAll();
        file.close();

        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
        if (parseError.error != QJsonParseError::NoError) {
            qWarning() << "JSON parse error:" << parseError.errorString();
            return;
        }
        if(doc.isArray())
        {
            QJsonArray array = doc.array();
            for(const QJsonValue &val : array)
            {
                QJsonObject obj = val.toObject();
                HistoryEntry entry;
                entry.url = obj["url"].toString();
                entry.title = obj["title"].toString();
                entry.timestamp = QDateTime::fromString(obj["timestamp"].toString(), Qt::ISODate);

                history.append(entry);
            }
        }
    }
}

void HistoryManager::clear()
{
    history.clear();
}
