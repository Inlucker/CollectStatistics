#ifndef JSONHANDLER_H
#define JSONHANDLER_H


#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include "Statistics.h"
#include "SQLiteDB.h"


class JSONHandler
{
public:
    JSONHandler(QString url, QString databaseParams, QObject* parent=nullptr);
    ~JSONHandler();

    QNetworkAccessManager* getManager();
    void getRequest(QString request);
    void saveResult(QNetworkReply* reply);
    QList<Statistics> getStatistics();
    void changeHost(QString url);

private:
    QString _url;
    QNetworkAccessManager* _manager;
    SQLiteDB* _database;
    QString _curRequestReply;
};

#endif // JSONHANDLER_H
