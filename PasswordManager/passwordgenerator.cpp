#include "passwordgenerator.h"

int checkOption(bool lowerCase, bool upperCase, bool digits, bool special)
{
    if (upperCase && lowerCase && digits && special)
        return 0;
    else if (upperCase && lowerCase && digits)
        return 1;
    else if (upperCase && lowerCase && special)
        return 2;
    else if (upperCase && digits && special)
        return 3;
    else if (lowerCase && digits && special)
        return 4;
    else if (upperCase && lowerCase)
        return 5;
    else if (upperCase && digits)
        return 6;
    else if (upperCase && special)
        return 7;
    else if (lowerCase && digits)
        return 8;
    else if (lowerCase && special)
        return 9;
    else if (digits && special)
        return 10;
    else if (upperCase)
        return 11;
    else if (lowerCase)
        return 12;
    else if (digits)
        return 13;
    else if (special)
        return 14;
    else
        return 15;
}

char lowerCaseGen()
{
    static const char alpha[27] = { 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110,
        110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122 };
    return alpha[rand() % 27];
}

char upperCaseGen()
{
    static const char alpha[27] = { 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78,
                                    79, 80, 81, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90 };
    return alpha[rand() % 27];
}

char digitsGen()
{
    static const char digits[10] = { 48, 49, 50, 51, 52, 53, 54, 55, 56, 57 };
    return digits[rand() % 10];
}

char specialGen()
{
    static const char special[31] = { 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 58,
                                    59, 60, 61, 62, 63, 64, 91, 92, 93, 94, 95, 123, 124, 125, 126 };
    return special[rand() % 31];
}

QString option0(unsigned int passLength)
{
    QString password = "";
    int random;

    for (unsigned int i = 0; i < passLength; i++)
    {
        random = rand() % 4;

        switch (random)
        {
            case 0: password += upperCaseGen(); break;
            case 1: password += lowerCaseGen(); break;
            case 2: password += digitsGen(); break;
            case 3: password += specialGen(); break;
        }
    }
    return password;
}

QString option1(unsigned int passLength)
{
    QString password = "";
    int random;

    for (unsigned int i = 0; i < passLength; i++)
    {
        random = rand() % 3;

        switch (random)
        {
            case 0: password += upperCaseGen(); break;
            case 1: password += lowerCaseGen(); break;
            case 2: password += digitsGen(); break;
        }
    }
    return password;
}

QString option2(unsigned int passLength)
{
    QString password = "";
    int random;

    for (unsigned int i = 0; i < passLength; i++)
    {
        random = rand() % 3;

        switch (random)
        {
            case 0: password += upperCaseGen(); break;
            case 1: password += lowerCaseGen(); break;
            case 2: password += specialGen(); break;
        }
    }
    return password;
}

QString option3(unsigned int passLength)
{
    QString password = "";
    int random;

    for (unsigned int i = 0; i < passLength; i++)
    {
        random = rand() % 3;

        switch (random)
        {
            case 0: password += upperCaseGen(); break;
            case 1: password += digitsGen(); break;
            case 2: password += specialGen(); break;
        }
    }
    return password;
}

QString option4(unsigned int passLength)
{
    QString password = "";
    int random;

    for (unsigned int i = 0; i < passLength; i++)
    {
        random = rand() % 3;

        switch (random)
        {
            case 0: password += lowerCaseGen(); break;
            case 1: password += digitsGen(); break;
            case 2: password += specialGen(); break;
        }
    }
    return password;
}

QString option5(unsigned int passLength)
{
    QString password = "";
    int random;

    for (unsigned int i = 0; i < passLength; i++)
    {
        random = rand() % 2;

        switch (random)
        {
            case 0: password += upperCaseGen(); break;
            case 1: password += lowerCaseGen(); break;
        }
    }
    return password;
}

QString option6(unsigned int passLength)
{
    QString password = "";
    int random;

    for (unsigned int i = 0; i < passLength; i++)
    {
        random = rand() % 2;

        switch (random)
        {
            case 0: password += upperCaseGen(); break;
            case 1: password += digitsGen(); break;
        }
    }
    return password;
}

QString option7(unsigned int passLength)
{
    QString password = "";
    int random;

    for (unsigned int i = 0; i < passLength; i++)
    {
        random = rand() % 2;

        switch (random)
        {
        case 0: password += upperCaseGen(); break;
        case 1: password += specialGen(); break;
        }
    }
    return password;
}

QString option8(unsigned int passLength)
{
    QString password = "";
    int random;

    for (unsigned int i = 0; i < passLength; i++)
    {
        random = rand() % 2;

        switch (random)
        {
        case 0: password += lowerCaseGen(); break;
        case 1: password += digitsGen(); break;
        }
    }
    return password;
}

QString option9(unsigned int passLength)
{
    QString password = "";
    int random;

    for (unsigned int i = 0; i < passLength; i++)
    {
        random = rand() % 2;

        switch (random)
        {
        case 0: password += lowerCaseGen(); break;
        case 1: password += specialGen(); break;
        }
    }
    return password;
}

QString option10(unsigned int passLength)
{
    QString password = "";
    int random;

    for (unsigned int i = 0; i < passLength; i++)
    {
        random = rand() % 2;

        switch (random)
        {
        case 0: password += digitsGen(); break;
        case 1: password += specialGen(); break;
        }
    }
    return password;
}

QString option11(unsigned int passLength)
{
    QString password = "";

    for (unsigned int i = 0; i < passLength; i++)
        password += upperCaseGen();
    return password;
}

QString option12(unsigned int passLength)
{
    QString password = "";

    for (unsigned int i = 0; i < passLength; i++)
        password += lowerCaseGen();
    return password;
}

QString option13(unsigned int passLength)
{
    QString password = "";

    for (unsigned int i = 0; i < passLength; i++)
        password += digitsGen();
    return password;
}

QString option14(unsigned int passLength)
{
    QString password = "";

    for (unsigned int i = 0; i < passLength; i++)
        password += specialGen();
    return password;
}

QString option15()
{
    QString password = "";
    return password;
}

QString PasswordGenerator::generatePassword(bool lowerCaseChars, bool upperCaseChars, bool digits, bool specialChars, int length)
{
    srand (time(NULL));
    switch (checkOption(lowerCaseChars, upperCaseChars, digits, specialChars))
        {
            case 0: return option0(length);  break;
            case 1: return option1(length);  break;
            case 2: return option2(length);  break;
            case 3: return option3(length);  break;
            case 4: return option4(length);  break;
            case 5: return option5(length);  break;
            case 6: return option6(length);  break;
            case 7: return option7(length);  break;
            case 8: return option8(length);  break;
            case 9: return option9(length);  break;
            case 10: return option10(length); break;
            case 11: return option11(length); break;
            case 12: return option12(length); break;
            case 13: return option13(length); break;
            case 14: return option14(length); break;
            case 15: return option15(); break;
        }
    return "";
}
