#include "JSONHandler.h"


JSONHandler::JSONHandler(QString url, QString databaseParams, QObject* parent): _url(url)
{
    _manager = new QNetworkAccessManager(parent);
    _database = new SQLiteDB(databaseParams);
}


JSONHandler::~JSONHandler()
{
    delete _manager;
    delete _database;
}


QNetworkAccessManager* JSONHandler::getManager()
{
    return _manager;
}


void JSONHandler::getRequest(QString request)
{
    QNetworkRequest networkRequest(QUrl(_url + request));
    _manager->get(networkRequest);
}


void JSONHandler::saveResult(QNetworkReply *reply)
{
    _curRequestReply = reply->readAll();
    QList<Statistics> statistics = getStatistics();
    _database->saveStatistics(statistics);
}


QList<Statistics> JSONHandler::getStatistics()
{
    QList<Statistics> resources;
    QJsonDocument document = QJsonDocument::fromJson(_curRequestReply.toUtf8());
    QJsonArray dongles = document["dongles"].toArray();

    for (auto dongle: dongles)
    {
        QJsonArray products = dongle.toObject()["products"].toArray();
        for (auto product: products)
        {
            QJsonArray features = product.toObject()["features"].toArray();
            for (auto feature: features)
            {
                QJsonObject featureObject = feature.toObject();
                int featureNumber = featureObject["featureNumber"].toInt();
                int freeResources = featureObject["floatingResource"].toInt();
                int busyResources = featureObject["maxConcurrentResource"].toInt() - freeResources;
                Statistics statistics(featureNumber, busyResources, freeResources, QDateTime::currentDateTime());
                resources.append(statistics);
            }
        }
    }
    return resources;
}
