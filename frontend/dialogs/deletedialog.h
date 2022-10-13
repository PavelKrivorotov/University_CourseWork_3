#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include "user/user.h"

#include <QDialog>
#include <QUrlQuery>

namespace Ui {
class DeleteDialog;
}

class DeleteDialog : public QDialog {
    Q_OBJECT

public:
    explicit DeleteDialog(QWidget *parent = nullptr);
    ~DeleteDialog();

    void setUserData(User *user);

private:
    QUrlQuery getQuery();

private:
    Ui::DeleteDialog *ui;

    User *_currentUser;

private slots:
    void onBtnYesClicked();

signals:
    void btnYesClicked(QUrlQuery urlQuery, QUrl urlAddr = QUrl("http://127.0.0.1:8000/api/delete-content/"));
};

#endif // DELETEDIALOG_H
