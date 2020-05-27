#ifndef LOGIN_H
#define LOGIN_H
#include <QString>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTextStream>
#include <QCryptographicHash>

class Login
{
public:
    static bool authenticate(QString login, QString password);
};

#endif // LOGIN_H
