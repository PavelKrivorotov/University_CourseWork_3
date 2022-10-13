#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include "user/user.h"

#include <QNetworkReply>


class Deserializer {

public:
    Deserializer(QNetworkReply *reply);
    virtual ~Deserializer();

    QList<User*> * getUserList();

    User * getCurrentUser();

    QString getErrors();

    QString toNormalize(QString str);

    bool isValid();

private:
    QList<User*> *_userList;
    User *_currentUser;

    bool _isValid;
    QStringList _errors;

private:
    void deserialize(QJsonDocument json);

    User * convertUser(QJsonObject userData);
};

#endif // DESERIALIZER_H
