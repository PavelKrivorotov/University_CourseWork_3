#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <user/usermanager.h>

#include "dialogs/adduserdialog.h"
#include "dialogs/changedialog.h"
#include "dialogs/deletedialog.h"
#include "dialogs/filterdialog.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow: public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    AddUserDialog * getAddUserDialog();

    ChangeDialog * getChangeDialog();

    DeleteDialog * getDeleteDialog();

    FilterDialog * getFilterDialog();

private:
//    void showData();

//    void insertRow(int index, User *addUser);

//    void refreshRow(int index, User *newUser);

//    void deleteRow();

//    void orderRows(int headerIndex);

    void setUser(int index, QString firstName, QString lastName, QString emailAddr,
                 QString birthDay, QString zodiacSign);

    void setRowCount();

    void setColCount();

    void setHorisontalLabels();

private:
    Ui::MainWindow *ui;

    FilterDialog *_filterDialog;
    AddUserDialog *_addUserDialog;
    ChangeDialog *_changeDialog;
    DeleteDialog *_deleteDialog;

    UserManager *_userManager;

private slots:
    void showData();

    void insertRow(int index, User *addUser);

    void refreshRow(int index, User *newUser);

    void deleteRow();

    void orderRows(int headerIndex);

    void onSearchBtnClicked();

signals:
    void btnSearchClicked(QUrlQuery urlQuery, QUrl urlAddr = QUrl("http://127.0.0.1:8000/api/get-content/"));
};

#endif // MAINWINDOW_H
