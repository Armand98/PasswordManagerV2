#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H
#include <QString>
#include <ctime>

class PasswordGenerator
{
public:
    static QString generatePassword(bool lowerCaseChars, bool upperCaseChars, bool digits, bool specialChars, int length);
};

#endif // PASSWORDGENERATOR_H
