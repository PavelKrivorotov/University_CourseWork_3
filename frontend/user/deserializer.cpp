#include "deserializer.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

Deserializer::Deserializer(QNetworkReply *reply) {
    _userList = nullptr;
    _currentUser = nullptr;
    _isValid = false;

    QJsonDocument json = QJsonDocument::fromJson(reply->readAll());

    deserialize(json);
}


Deserializer::~Deserializer() {

}


void Deserializer::deserialize(QJsonDocument json) {
    if (json.isEmpty()) {
        _errors << "No connect to server!";
    }

    else if (json["error"].toBool()) {
        QJsonObject errors = json["errors"].toObject();
        QStringList keys = errors.keys();

        for (int ind = 0; ind < keys.size(); ind++) {
            QJsonArray values = errors.take(keys.value(ind)).toArray();
            QStringList list;

            for (int ind_2 = 0; ind_2 < values.size(); ind_2++) {
                list << values.at(ind_2).toString();
            }

            _errors << QString(keys.value(ind)) + QString(": ") + QString(list.join(". "));
        }
    }

    else if (json["many"].toBool()) {
        _userList = new QList<User*>;
        _isValid = true;

        QJsonArray array = json["content"].toArray();

        for (int ind = 0; ind < array.size(); ind++) {
            QJsonObject userData = array.at(ind).toObject();
            User *user = convertUser(userData);
            _userList->append(user);
        }
    }

    else {
        _isValid = true;

        QJsonObject userData = json["content"].toObject();
        _currentUser = convertUser(userData);
    }
}


User * Deserializer::convertUser(QJsonObject userData) {
    User *user = new User();

    user->setFirstName(toNormalize(userData["first_name"].toString()));
    user->setLastName(toNormalize(userData["last_name"].toString()));
    user->setEmailAddr(userData["email"].toString());
    user->setBirthDay(userData["birthday"].toString());
    user->setZodiacSign(toNormalize(userData["zodiac"].toString()));

    return user;
}


QList<User*> * Deserializer::getUserList() {
    return _userList;
}


User * Deserializer::getCurrentUser() {
    return _currentUser;
}


QString Deserializer::getErrors() {
    return _errors.join("\n");
}


QString Deserializer::toNormalize(QString str) {
    QString newFirst = str.at(0).toUpper();
    str.replace(0, 1, newFirst);
    return str;
}


bool Deserializer::isValid() {
    return _isValid;
}
