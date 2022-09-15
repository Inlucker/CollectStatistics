#ifndef STATISTICS_H
#define STATISTICS_H

#include <QDateTime>

class Statistics
{
public:
    Statistics(int featureNumber, int busyResources, int freeResources, QDateTime dateTime):
        _featureNumber(featureNumber), _busyResources(busyResources), _freeResources(freeResources), _dateTime(dateTime) {};
    ~Statistics() = default;

    int getFeatureNumber() const;
    int getBusyResources() const;
    int getFreeResources() const;
    QDateTime getDateTime() const;

    void setFeatureNumber(int value);
    void setBusyResources(int value);
    void setFreeResources(int value);
    void setDateTime(QDateTime value);

private:
    int _featureNumber;
    int _busyResources;
    int _freeResources;
    QDateTime _dateTime;
};


#endif // STATISTICS_H
