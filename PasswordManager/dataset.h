#ifndef DATASET_H
#define DATASET_H
#include <QString>

class DataSet
{
public:
    DataSet(QString site, QString login, QString password);
    DataSet(QString site, QString login, QString password, int datasetCounter);

    QString getSite() const;
    void setSite(const QString &value);

    QString getLogin() const;
    void setLogin(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    int getDatasetCounter() const;
    void setDatasetCounter(int value);

private:
    QString site;
    QString login;
    QString password;
    int datasetCounter;

};

bool operator<(const DataSet &d1, const DataSet &d2);

#endif // DATASET_H
