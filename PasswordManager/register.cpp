#include "register.h"

bool Register::addNewAccount(QString login, QString password)
{
    if(!QDir("C:\\ProgramData\\MyPasswordManager").exists()) {
        QDir().mkdir("C:\\ProgramData\\MyPasswordManager");
    }

    QFile file("C:\\ProgramData\\MyPasswordManager\\users.json");
    QString loginHash = QString(QCryptographicHash::hash(login.toUtf8(),QCryptographicHash::Keccak_512).toHex());
    QString passwordHash = QString(QCryptographicHash::hash(password.toUtf8(),QCryptographicHash::Keccak_512).toHex());

    QTextStream textStream(&file);
    QString jsonString;

    if(file.open(QIODevice::ReadOnly)) {
     jsonString = textStream.readAll();
     file.close();
    }

    QByteArray jsonBytes = jsonString.toLocal8Bit();
    auto jsonDocument = QJsonDocument::fromJson(jsonBytes);
    QJsonObject jsonObject=jsonDocument.object();
    QVariantMap map = jsonObject.toVariantMap();
    map.insert(loginHash, passwordHash);
    QJsonObject jsonObj = QJsonObject::fromVariantMap(map);

    file.open(QIODevice::WriteOnly);
    QJsonDocument finalJsonDocument;
    finalJsonDocument.setObject(jsonObj);
    file.write(finalJsonDocument.toJson());
    file.close();

    return true;
}

bool Register::accountNotUsed(QString login)
{
    QFile file("C:\\ProgramData\\MyPasswordManager\\users.json");
    QString loginHash = QString(QCryptographicHash::hash(login.toUtf8(),QCryptographicHash::Keccak_512).toHex());

    QTextStream textStream(&file);
    QString jsonString;

    if(file.open(QIODevice::ReadOnly)) {
        jsonString = textStream.readAll();
        file.close();
    }

    QByteArray jsonBytes = jsonString.toLocal8Bit();
    auto jsonDocument = QJsonDocument::fromJson(jsonBytes);
    QJsonObject jsonObject=jsonDocument.object();
    QVariantMap map = jsonObject.toVariantMap();
    QStringList keysAsArray = map.keys();

    foreach(QString key, keysAsArray) {
        if(key == loginHash) {
            return false;
        }
    }

    return true;
}
