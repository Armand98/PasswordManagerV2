#include "login.h"

bool Login::authenticate(QString login, QString password)
{
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
    QStringList keysAsArray = map.keys();

    foreach(QString key, keysAsArray) {
        if(key == loginHash) {
            if(map.value(key) == passwordHash) {
                return true;
            }
        }
    }

    return false;
}
