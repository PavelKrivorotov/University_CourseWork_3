#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "user/user.h"

#include <QMessageBox>

#include <QNetworkAccessManager>
#include <QNetworkReply>


class MainWindow;

class UserManager: public QObject {
    Q_OBJECT

public:
    explicit UserManager(MainWindow *parent = nullptr);
    ~UserManager();

    QList<User*> * getUserList();

    void changeUserList(QNetworkReply *reply);

    void addUser(QNetworkReply *reply);

    void changeUser(QNetworkReply *reply);

    void deleteUser(QNetworkReply *reply);

private:
    void get(QUrlQuery urlQuery, QUrl urlAddr);

    void post(QByteArray data, QUrl urlAddr);

    void put(QByteArray data, QUrl urlAddr);

    void del(QUrlQuery urlQuery, QUrl urlAddr);

    void showMessage(QMessageBox::Icon icon, QString title, QString text);

    void deleterUserList();

    int searchUserByEmailAddr(QString emailAddr);

private:
    QList<User*> *_userList;
    QNetworkAccessManager *_manager;

    QMessageBox *_messageBox;

signals:
    void showDataSignal();

    void addUserSignal(int index, User *addUser);

    void changeUserSignal(int index, User *newUser);

    void deleteUserSignal();
};

#endif // USERMANAGER_H
