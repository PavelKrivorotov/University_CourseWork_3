#ifndef USER_H
#define USER_H

#include <QString>
#include <QStringList>


class User {

public:
    explicit User(QString firstName, QString lastName, QString emailAddr, QString birthDay, QString zodiacSign = "");
    User();
    virtual ~User();

    QString getEmailAddr();

    QString getFirstName();

    QString getLastName();

    QString getBirthDay();

    QString getZodiacSign();

    void setEmailAddr(QString emailAddr);

    void setFirstName(QString firstName);

    void setLastName(QString lastName);

    void setBirthDay(QString birthDay);

    void setZodiacSign(QString zodiacSign);

private:
    QString _emailAddr;
    QString _firstName;
    QString _lastName;
    QString _birthDay;
    QString _zodiacSign;

    bool _is_valid;
    QStringList _errors;
};

#endif // USER_H
