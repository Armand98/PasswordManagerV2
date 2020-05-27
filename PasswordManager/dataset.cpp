#include "dataset.h"

DataSet::DataSet(QString site, QString login, QString password)
{
    this->site = site;
    this->login = login;
    this->password = password;
}

DataSet::DataSet(QString site, QString login, QString password, int datasetCounter)
{
    this->site = site;
    this->login = login;
    this->password = password;
    this->datasetCounter = datasetCounter;
}

QString DataSet::getSite() const
{
    return site;
}

void DataSet::setSite(const QString &value)
{
    site = value;
}

QString DataSet::getLogin() const
{
    return login;
}

void DataSet::setLogin(const QString &value)
{
    login = value;
}

QString DataSet::getPassword() const
{
    return password;
}

void DataSet::setPassword(const QString &value)
{
    password = value;
}

int DataSet::getDatasetCounter() const
{
    return datasetCounter;
}

void DataSet::setDatasetCounter(int value)
{
    datasetCounter = value;
}

bool operator<(const DataSet &d1, const DataSet &d2)
{
    return d1.getDatasetCounter() > d2.getDatasetCounter();
}
