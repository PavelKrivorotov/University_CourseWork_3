#include "user.h"

User::User(QString firstName, QString lastName, QString emailAddr, QString birthDay, QString zodiacSign) {
    _firstName = firstName;
    _lastName = lastName;
    _emailAddr = emailAddr;
    _birthDay = birthDay;
    _zodiacSign = zodiacSign;
}


User::User() {

}


User::~User() {

}


QString User::getEmailAddr() {
    return _emailAddr;
}


QString User::getFirstName() {
    return _firstName;
}


QString User::getLastName() {
    return _lastName;
}


QString User::getBirthDay() {
    return _birthDay;
}


QString User::getZodiacSign() {
    return _zodiacSign;
}


void User::setEmailAddr(QString emailAddr) {
    _emailAddr = emailAddr;
}


void User::setFirstName(QString firstName) {
    _firstName = firstName;
}


void User::setLastName(QString lastName) {
    _lastName = lastName;
}


void User::setBirthDay(QString birthDay) {
    _birthDay = birthDay;
}


void User::setZodiacSign(QString zodiacSign) {
    _zodiacSign = zodiacSign;
}

