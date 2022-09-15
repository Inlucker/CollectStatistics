#ifndef SQLITEDB_H
#define SQLITEDB_H


#include <QList>
#include <iostream>
#include <string>
#include <QDebug>
#include "Statistics.h"
#include <QtSql>


class SQLiteDB
{
public:
    SQLiteDB(QString params);
    ~SQLiteDB() = default;

    void saveStatistics(QList<Statistics> statistics);

private:
    QString dateTimeToQString(QDateTime dateTime);

private:
    QString _params;
    QSqlDatabase _sdb;
};


#endif // SQLITEDB_H
