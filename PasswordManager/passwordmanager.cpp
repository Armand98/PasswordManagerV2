#include "passwordmanager.h"

PasswordManager::PasswordManager(QString login, QString password)
{
    this->KEY = password;
    this->IV = login;
}

bool PasswordManager::isSiteAlreadyUsed(QString site)
{
    foreach(DataSet element, datasetList) {
        DataSet decryptedElement = decryptDataset(element);
        if(decryptedElement.getSite() == site) {
            return true;
        }
    }

    return false;
}

void PasswordManager::saveDatasetList()
{
    QString path = "C:\\ProgramData\\MyPasswordManager\\data" + getIV() + ".json";
    QFile file(path);

    QTextStream textStream(&file);
    QJsonArray jsonArray;

    sortDatasetListByCounter();

    for(int i=0; i<datasetList.count(); i++) {
        QVariantMap map;
        map.insert("site", datasetList.at(i).getSite());
        map.insert("login", datasetList.at(i).getLogin());
        map.insert("password", datasetList.at(i).getPassword());
        map.insert("counter", QString::number(datasetList.at(i).getDatasetCounter()));
        QJsonObject jsonObj = QJsonObject::fromVariantMap(map);
        jsonArray.append(jsonObj);
    }

    file.open(QIODevice::WriteOnly);
    QJsonDocument finalJsonDocument;
    finalJsonDocument.setArray(jsonArray);
    file.write(finalJsonDocument.toJson());
    file.close();
}

void PasswordManager::loadDatasetListFromFile()
{
    QString path = "C:\\ProgramData\\MyPasswordManager\\data" + getIV() + ".json";
    QFile file(path);

    QTextStream textStream(&file);
    QString jsonString;

    if(file.open(QIODevice::ReadOnly)) {
        jsonString = textStream.readAll();
        file.close();
    }

    QByteArray jsonBytes = jsonString.toLocal8Bit();
    auto jsonDocument = QJsonDocument::fromJson(jsonBytes);
    QJsonArray jsonArray = jsonDocument.array();

    for(int i=0; i<jsonArray.count(); i++) {
        QJsonObject jsonObject = jsonArray.at(i).toObject();
        QVariantMap map = jsonObject.toVariantMap();
        QString site = map.value("site").toString();
        QString login = map.value("login").toString();
        QString password = map.value("password").toString();
        int elementCounter = map.value("counter").toInt();

        DataSet newDataset(site,login,password, elementCounter);
        datasetList.append(newDataset);
    }
    sortDatasetListByCounter();
}

void PasswordManager::updateDatasetElement(QString site)
{
    for(int i=0; i<datasetList.count(); i++) {
        DataSet decryptedElement = decryptDataset(datasetList.at(i));
        if(decryptedElement.getSite() == site) {
            DataSet dataset(site, decryptedElement.getLogin(), decryptedElement.getPassword(), decryptedElement.getDatasetCounter()+1);
            DataSet encryptedDataset = encryptDataset(dataset);
            datasetList.replace(i, encryptedDataset);
            break;
        }
    }
    saveDatasetList();
}

void PasswordManager::updateDatasetElement(QString site, QString login, QString password)
{
    for(int i=0; i<datasetList.count(); i++) {
        DataSet decryptedElement = decryptDataset(datasetList.at(i));
        if(decryptedElement.getSite() == site) {
            DataSet dataset(site, login, password, decryptedElement.getDatasetCounter());
            DataSet encryptedDataset = encryptDataset(dataset);
            datasetList.replace(i, encryptedDataset);
            break;
        }
    }
    saveDatasetList();
}

void PasswordManager::deleteDatasetElement(QString site)
{
    for(int i=0; i<datasetList.count(); i++) {
        DataSet decryptedElement = decryptDataset(datasetList.at(i));
        if(decryptedElement.getSite() == site) {
            datasetList.removeAt(i);
            break;
        }
    }

    saveDatasetList();
}

void PasswordManager::sortDatasetListByCounter()
{
    std::sort(datasetList.begin(), datasetList.end());
}

void PasswordManager::deleteAllData()
{
    datasetList.clear();
    saveDatasetList();
}

int PasswordManager::getDatasetListSize()
{
    return datasetList.count();
}

DataSet PasswordManager::getDatasetListAt(int index)
{
    DataSet decodedElement = decryptDataset(datasetList.at(index));
    return decodedElement;
}

DataSet *PasswordManager::getDatasetItem(QString site)
{
    foreach(DataSet element, datasetList) {
        DataSet decodedElement = decryptDataset(element);
        QString elementSite = decodedElement.getSite();
        if(elementSite == site) {
            return new DataSet(decodedElement.getSite(), decodedElement.getLogin(), decodedElement.getPassword());
        }
    }
    return NULL;
}

DataSet PasswordManager::encryptDataset(DataSet dataset)
{
    QString site = dataset.getSite();
    QString login = dataset.getLogin();
    QString password = dataset.getPassword();

    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);

    QByteArray hashKey = QCryptographicHash::hash(getKEY().toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(getIV().toLocal8Bit(), QCryptographicHash::Md5);

    QByteArray encodedSite = encryption.encode(site.toLocal8Bit(), hashKey, hashIV);
    QByteArray encodedLogin = encryption.encode(login.toLocal8Bit(), hashKey, hashIV);
    QByteArray encodedPassword = encryption.encode(password.toLocal8Bit(), hashKey, hashIV);

    QString encodedSiteStr = QString::fromLocal8Bit(encodedSite);
    QString encodedLoginStr = QString::fromLocal8Bit(encodedLogin);
    QString encodedPasswordStr = QString::fromLocal8Bit(encodedPassword);

    return DataSet(encodedSiteStr, encodedLoginStr, encodedPasswordStr, dataset.getDatasetCounter());

}

DataSet PasswordManager::decryptDataset(DataSet dataset)
{
    QByteArray hashKey = QCryptographicHash::hash(getKEY().toLocal8Bit(), QCryptographicHash::Sha256);
    QByteArray hashIV = QCryptographicHash::hash(getIV().toLocal8Bit(), QCryptographicHash::Md5);

    QString encryptedSite = dataset.getSite();
    QString encryptedLogin = dataset.getLogin();
    QString encryptedPassword = dataset.getPassword();

    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);

    QByteArray decodedSite = encryption.decode(encryptedSite.toLocal8Bit(), hashKey, hashIV);
    QByteArray decodedLogin = encryption.decode(encryptedLogin.toLocal8Bit(), hashKey, hashIV);
    QByteArray decodedPassword = encryption.decode(encryptedPassword.toLocal8Bit(), hashKey, hashIV);

    QString decodedSiteStr = QString(encryption.removePadding(decodedSite));
    QString decodedLoginStr = QString(encryption.removePadding(decodedLogin));
    QString decodedPasswordStr = QString(encryption.removePadding(decodedPassword));

    return DataSet(decodedSiteStr, decodedLoginStr, decodedPasswordStr, dataset.getDatasetCounter());
}

QString PasswordManager::getKEY() const
{
    return KEY;
}

QString PasswordManager::getIV() const
{
    return IV;
}

void PasswordManager::addNewDatasetToTheList(DataSet dataset)
{
    DataSet encryptedDataset = encryptDataset(dataset);
    datasetList.append(encryptedDataset);
    saveDatasetList();
}
