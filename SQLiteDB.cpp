#include "SQLiteDB.h"

SQLiteDB::SQLiteDB(QString params): _params(params)
{
    _sdb = QSqlDatabase::addDatabase("QSQLITE");
    _sdb.setDatabaseName(params);

    if (!_sdb.open())
        qDebug() << _sdb.lastError().text();

    QSqlQuery query("create table if not exists sessions_info\
                    (\
                      id INTEGER PRIMARY KEY AUTOINCREMENT,\
                      time DATETIME,\
                      feature INTEGER NOT NULL CHECK(feature >= 0),\
                      free INTEGER NOT NULL CHECK(free >= 0),\
                      busy INTEGER NOT NULL CHECK(busy >= 0)\
                    );");
}

void SQLiteDB::saveStatistics(QList<Statistics> statistics)
{
    for (const auto &stats : statistics)
    {
        QString queryStr = "insert into sessions_info (time, feature, free, busy) values('";
        queryStr += dateTimeToQString(stats.getDateTime()) + "' , ";
        queryStr += QString::number(stats.getFeatureNumber()) + ", ";
        queryStr += QString::number(stats.getFreeResources()) + ", ";
        queryStr += QString::number(stats.getBusyResources()) + ");";
        QSqlQuery query(queryStr);
    }
}

QString SQLiteDB::dateTimeToQString(QDateTime dateTime)
{
    QString str = "";
    str += QString::number(dateTime.date().year()) + "-";
    str += QString::number(dateTime.date().month()) + "-";
    str += QString::number(dateTime.date().day()) + " ";
    str += QString::number(dateTime.time().hour()) + ":";
    str += QString::number(dateTime.time().minute()) + ":";
    str += QString::number(dateTime.time().second());
    return str;
}
