#ifndef REGISTER_H
#define REGISTER_H
#include <QString>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTextStream>
#include <QCryptographicHash>
#include <QDir>

class Register
{
public:
    static bool addNewAccount(QString login, QString password);
    static bool accountNotUsed(QString login);
};

#endif // REGISTER_H
