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

void HistoryManager::removeEntry(const QDateTime &timestamp)
{
    auto it = std::find_if(history.begin(), history.end(), [&](const HistoryEntry& entry){
        return entry.timestamp == timestamp;
    });

    if(it != history.end())
        history.erase(it);
}

const QList<HistoryEntry> &HistoryManager::getEntries() const
{
    return history;
}

QString HistoryManager::simplifyUrl(const QString& rawUrl)
{
    const QUrl url(rawUrl);

// Удалить созранение новой вклаки в историю
    if (url.scheme() == "qrc") {
        if (url.path().contains("newtab.html"))
            return "New Tab Page";
        else
            return "Internal Page";
    }

    if (url.scheme() == "file")
        return QFileInfo(url.toLocalFile()).fileName();

    QString host = url.host();
    if (host.startsWith("www."))
        host = host.mid(4);

    return host.isEmpty() ? rawUrl : host;
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
