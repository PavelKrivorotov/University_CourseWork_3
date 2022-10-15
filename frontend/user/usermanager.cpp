#include "usermanager.h"
#include "mainwindow.h"

#include "deserializer.h"

#include <QJsonObject>
#include <QJsonDocument>


UserManager::UserManager(MainWindow *parent) {
    _userList = new QList<User*>;
    _manager = new QNetworkAccessManager(this);
    _messageBox = new QMessageBox(QMessageBox::NoIcon, "", "");

    connect(parent->getAddUserDialog(), &AddUserDialog::btnAddClicked, this, &UserManager::post);
    connect(parent->getChangeDialog(), &ChangeDialog::btnYesClicked, this, &UserManager::put);
    connect(parent->getDeleteDialog(), &DeleteDialog::btnYesClicked, this, &UserManager::del);
    connect(parent, &MainWindow::btnSearchClicked, this, &UserManager::get);
}


UserManager::~UserManager() {
    deleterUserList();
    delete _manager;
    delete _messageBox;
}


QList<User*> * UserManager::getUserList() {
    return _userList;
}


void UserManager::changeUserList(QNetworkReply *reply) {
    Deserializer *ser = new Deserializer(reply);

    if (ser->isValid()) {
        // Clean old _userList and delete them;
         deleterUserList();

        _userList = ser->getUserList();
        showDataSignal();

        delete ser;
        delete reply;
        return;
    }

    qDebug() << "Is valid: " << ser->isValid() << "\n Errors: " << ser->getErrors();


    QString error = ser->getErrors();
    showMessage(QMessageBox::Critical, "Select error!", error);


    delete ser;
    delete reply;
}


void UserManager::addUser(QNetworkReply *reply) {
    Deserializer *ser = new Deserializer(reply);

    if (ser->isValid()) {
        User *user = ser->getCurrentUser();
        int index = _userList->size();

        _userList->append(user);
        addUserSignal(index, user);

        delete ser;
        delete reply;
        return;
    }

    qDebug() << "Is valid: " << ser->isValid() << "\n Errors: " << ser->getErrors();


    QString error = ser->getErrors();
    showMessage(QMessageBox::Critical, "Add error!", error);


    delete ser;
    delete reply;
}


void UserManager::changeUser(QNetworkReply *reply) {
    Deserializer *ser = new Deserializer(reply);

    if (ser->isValid()) {
        User *newUser = ser->getCurrentUser();
        int index = searchUserByEmailAddr(newUser->getEmailAddr());

        User *oldUser = _userList->value(index);
        delete oldUser;

        _userList->replace(index, newUser);
        changeUserSignal(index, newUser);

        delete ser;
        delete reply;
        return;
    }

    qDebug() << "Is valid: " << ser->isValid() << "\n Errors: " << ser->getErrors();


    QString error = ser->getErrors();
    showMessage(QMessageBox::Critical, "Change error!", error);


    delete ser;
    delete reply;
}


void UserManager::deleteUser(QNetworkReply *reply) {
    Deserializer *ser = new Deserializer(reply);

    if (ser->isValid()) {
        User *newUser = ser->getCurrentUser();
        int index = searchUserByEmailAddr(newUser->getEmailAddr());
        delete newUser;

        User *oldUser = _userList->value(index);
        delete oldUser;

        _userList->removeAt(index);
        deleteUserSignal();

        delete ser;
        delete reply;
        return;
    }

    qDebug() << "Is valid: " << ser->isValid() << "\n Errors: " << ser->getErrors();


    QString error = ser->getErrors();
    showMessage(QMessageBox::Critical, "Delete error!", error);


    delete ser;
    delete reply;
}


void UserManager::get(QUrlQuery urlQuery, QUrl urlAddr) {
    QUrl url = urlAddr;
    url.setQuery(urlQuery);

    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setUrl(url);

    QNetworkReply *reply =  _manager->get(request);
    connect(reply, &QNetworkReply::finished, [this, reply](){
        changeUserList(reply);
    });

    qDebug() << url;
}


void UserManager::post(QByteArray data, QUrl urlAddr) {
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setUrl(urlAddr);

    QNetworkReply *reply = _manager->post(request, data);
    connect(reply, &QNetworkReply::finished, [this, reply](){
        addUser(reply);
    });

    qDebug() << "Post query : " << QJsonDocument::fromJson(data);
}


void UserManager::put(QByteArray data, QUrl urlAddr) {
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setUrl(urlAddr);

    QNetworkReply *reply = _manager->put(request, data);
    connect(reply, &QNetworkReply::finished, [this, reply](){
        changeUser(reply);
    });

    qDebug() << "Put query : " << QJsonDocument::fromJson(data);
}


void UserManager::del(QUrlQuery urlQuery, QUrl urlAddr) {
    QUrl url = urlAddr;
    url.setQuery(urlQuery);

    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setUrl(url);

    QNetworkReply *reply = _manager->deleteResource(request);
    connect(reply, &QNetworkReply::finished, [this, reply](){
        deleteUser(reply);
    });

    qDebug() << url ;
}


void UserManager::sortUserList(int userAttributeIndex) {
    if ((userAttributeIndex != 0) && (userAttributeIndex != 1)) { return; }

    for (int index1 = 0; index1 < _userList->size() - 1; index1++) {
        for (int index2 = index1 + 1; index2 < _userList->size(); index2++) {
            User *currentUser = _userList->at(index1);
            User *nextUser = _userList->at(index2);

            switch (userAttributeIndex) {
                case 0:
                    if (nextUser->getFirstName() < currentUser->getFirstName()) {
                        _userList->replace(index1, nextUser);
                        _userList->replace(index2, currentUser);
                    }
                    break;

                case 1:
                    if (nextUser->getLastName() < currentUser->getLastName()) {
                        _userList->replace(index1, nextUser);
                        _userList->replace(index2, currentUser);
                    }
                    break;

                default:
                    break;
            }
        }
    }
}


void UserManager::showMessage(QMessageBox::Icon icon, QString title, QString text) {
    _messageBox->setIcon(icon);
    _messageBox->setWindowTitle(title);
    _messageBox->setText(text);
    _messageBox->exec();
}


void UserManager::deleterUserList() {
    for (int index = 0; index < _userList->size(); index++) {
        delete _userList->value(index);
    }

    delete _userList;
}


int UserManager::searchUserByEmailAddr(QString emailAddr) {
    for (int index = 0; index < _userList->size(); index++) {
        if (emailAddr == _userList->value(index)->getEmailAddr()) {
            return index;
        }
    }

    return -1;
}

