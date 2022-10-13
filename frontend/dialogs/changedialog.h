#ifndef CHANGEDIALOG_H
#define CHANGEDIALOG_H

#include "user/user.h"

#include <QDialog>
#include <QUrl>

namespace Ui {
class ChangeDialog;
}

class ChangeDialog : public QDialog {
    Q_OBJECT

public:
    explicit ChangeDialog(QWidget *parent = nullptr);
    ~ChangeDialog();

    void setUserData(User *user);

private:
    QByteArray getData();

private:
    Ui::ChangeDialog *ui;

    User *_currentUser;

private slots:
    void onBtnYesClicked();

signals:
    void btnYesClicked(QByteArray data, QUrl urlAddr = QUrl("http://127.0.0.1:8000/api/update-content/"));
};

#endif // CHANGEDIALOG_H
