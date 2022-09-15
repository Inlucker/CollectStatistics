#include "Statistics.h"


int Statistics::getFeatureNumber() const
{
    return _featureNumber;
}


int Statistics::getBusyResources() const
{
    return _busyResources;
}


int Statistics::getFreeResources() const
{
    return _freeResources;
}


QDateTime Statistics::getDateTime() const
{
    return _dateTime;
}


void Statistics::setFeatureNumber(int value)
{
    _featureNumber = value;
}


void Statistics::setBusyResources(int value)
{
    _busyResources = value;
}


void Statistics::setFreeResources(int value)
{
    _freeResources = value;
}


void Statistics::setDateTime(QDateTime value)
{
    _dateTime = value;
}
