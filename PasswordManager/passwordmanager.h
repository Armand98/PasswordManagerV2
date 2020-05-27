#ifndef PASSWORDMANAGER_H
#define PASSWORDMANAGER_H
#include <QString>
#include "dataset.h"
#include <QVector>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QTextStream>
#include <QCryptographicHash>
#include <AES/qaesencryption.h>
#include <algorithm>

class PasswordManager
{
public:
    PasswordManager(QString login, QString password);
    bool isSiteAlreadyUsed(QString site);
    void saveDatasetList();
    void addNewDatasetToTheList(DataSet dataset);
    void loadDatasetListFromFile();
    void updateDatasetElement(QString site, QString login, QString password);
    void updateDatasetElement(QString site);
    void deleteDatasetElement(QString site);
    void updateDatasetItemCounter(QString site);
    void sortDatasetListByCounter();
    void deleteAllData();
    int getDatasetListSize();
    DataSet getDatasetListAt(int index);
    DataSet *getDatasetItem(QString site);
    DataSet encryptDataset(DataSet dataset);
    DataSet decryptDataset(DataSet dataset);

private:
    QVector<DataSet> datasetList;
    QString KEY;
    QString IV;
    QString getKEY() const;
    QString getIV() const;


};

#endif // PASSWORDMANAGER_H
