#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    _filterDialog = new FilterDialog(this);
    _addUserDialog = new AddUserDialog(this);
    _changeDialog = new ChangeDialog(this);
    _deleteDialog = new DeleteDialog(this);

    _userManager = new UserManager(this);

    setColCount();
    setRowCount();
    setHorisontalLabels();

    ui->ContentTW->show();

    connect(ui->AddUserBtn, &QPushButton::clicked, _addUserDialog, &AddUserDialog::show);
    connect(ui->FilterBtn, &QPushButton::clicked, _filterDialog, &FilterDialog::show);
    connect(ui->SearchBtn, &QPushButton::clicked, this, &MainWindow::onSearchBtnClicked);

    connect(_userManager, &UserManager::showDataSignal, this, &MainWindow::showData);
    connect(_userManager, &UserManager::addUserSignal, this, &MainWindow::insertRow);
    connect(_userManager, &UserManager::changeUserSignal, this, &MainWindow::refreshRow);
    connect(_userManager, &UserManager::deleteUserSignal, this, &MainWindow::deleteRow);

    connect(ui->ContentTW->horizontalHeader(), &QHeaderView::sectionClicked, this, &MainWindow::orderRows);
}


MainWindow::~MainWindow(){
    delete ui;

    delete _filterDialog;
    delete _addUserDialog;
    delete _changeDialog;
    delete _deleteDialog;

    delete _userManager;
}


AddUserDialog * MainWindow::getAddUserDialog() {
    return _addUserDialog;
}


ChangeDialog * MainWindow::getChangeDialog() {
    return _changeDialog;
}


DeleteDialog * MainWindow::getDeleteDialog() {
    return _deleteDialog;
}


FilterDialog * MainWindow::getFilterDialog() {
    return _filterDialog;
}


void MainWindow::showData() {
    setRowCount();
    ui->ContentTW->clearContents();

    QList<User*> *userList = _userManager->getUserList();
    for (int index = 0; index < userList->length(); index++) {
        User *user = userList->value(index);
        setUser(index, user->getFirstName(), user->getLastName(), user->getEmailAddr(),
                user->getBirthDay(), user->getZodiacSign());
    }
}


void MainWindow::insertRow(int index, User *addUser) {
    setRowCount();
    setUser(index, addUser->getFirstName(), addUser->getLastName(), addUser->getEmailAddr(),
            addUser->getBirthDay(), addUser->getZodiacSign());
}


void MainWindow::refreshRow(int index, User *newUser) {
    ui->ContentTW->removeRow(index);
    ui->ContentTW->insertRow(index);
    setUser(index, newUser->getFirstName(), newUser->getLastName(), newUser->getEmailAddr(),
            newUser->getBirthDay(), newUser->getZodiacSign());
}


void MainWindow::deleteRow() {
    showData();
}


void MainWindow::orderRows(int headerIndex) {
    _userManager->sortUserList(headerIndex);
    showData();

    qDebug() << "Click to horizontalHeaderItem: " << headerIndex;
}


void MainWindow::setUser(int index, QString firstName, QString lastName, QString emailAddr,
                         QString birthDay, QString zodiacSign){
    QLabel *_firstName = new QLabel(ui->ContentTW);
    _firstName->setText(firstName);
    _firstName->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QLabel *_lastName = new QLabel(ui->ContentTW);
    _lastName->setText(lastName);
    _lastName->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QLabel *_emailAddr = new QLabel(ui->ContentTW);
    _emailAddr->setText(emailAddr);
    _emailAddr->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QLabel *_birthDay = new QLabel(ui->ContentTW);
    _birthDay->setText(birthDay);
    _birthDay->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QLabel *_zodiacSign = new QLabel(ui->ContentTW);
    _zodiacSign->setText(zodiacSign);
    _zodiacSign->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QPushButton *changeBtn = new QPushButton(ui->ContentTW);
    changeBtn->setIcon(QIcon(":/icon/icons/change_icon.png"));
    changeBtn->setIconSize(QSize(25, 25));

    QPushButton *delBtn = new QPushButton(ui->ContentTW);
    delBtn->setIcon(QIcon(":/icon/icons/delete_icon.png"));
    delBtn->setIconSize(QSize(25, 25));


    connect(changeBtn, &QPushButton::clicked, _changeDialog, [this, index](){
        _changeDialog->setUserData(_userManager->getUserList()->value(index));
        _changeDialog->show();
    });

    connect(delBtn, &QPushButton::clicked, _deleteDialog, [this, index](){
        _deleteDialog->setUserData(_userManager->getUserList()->value(index));
        _deleteDialog->show();
    });


    ui->ContentTW->setCellWidget(index, 0, _firstName);
    ui->ContentTW->setCellWidget(index, 1, _lastName);
    ui->ContentTW->setCellWidget(index, 2, _emailAddr);
    ui->ContentTW->setCellWidget(index, 3, _birthDay);
    ui->ContentTW->setCellWidget(index, 4, _zodiacSign);
    ui->ContentTW->setCellWidget(index, 5, changeBtn);
    ui->ContentTW->setCellWidget(index, 6, delBtn);
}


void MainWindow::setRowCount() {
    int count = _userManager->getUserList()->size();
    ui->ContentTW->setRowCount(count);
}


void MainWindow::setColCount() {
    ui->ContentTW->setColumnCount(7);
}


void MainWindow::setHorisontalLabels() {
    QStringList headerLabels;

    headerLabels.append("Имя");
    headerLabels.append("Фамилия");
    headerLabels.append("Почта");
    headerLabels.append("День рождения");
    headerLabels.append("Знак зодиака");
    headerLabels.append("Редактировать");
    headerLabels.append("Удалить");

    ui->ContentTW->setHorizontalHeaderLabels(headerLabels);
}


void MainWindow::onSearchBtnClicked() {
    QUrlQuery urlQuery = _filterDialog->getQuery();
    btnSearchClicked(urlQuery);
}

