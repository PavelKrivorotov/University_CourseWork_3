#include "deletedialog.h"
#include "ui_deletedialog.h"


DeleteDialog::DeleteDialog(QWidget *parent): QDialog(parent), ui(new Ui::DeleteDialog) {
    ui->setupUi(this);

    connect(ui->YespBtn, &QPushButton::clicked, this, &DeleteDialog::onBtnYesClicked);
    connect(ui->NopBtn, &QPushButton::clicked, this, &DeleteDialog::close);
}


DeleteDialog::~DeleteDialog() {
    delete ui;
}


void DeleteDialog::setUserData(User *user) {
    _currentUser = user;

    ui->FirstNameLE->setText(user->getFirstName());
    ui->LastNameLE->setText(user->getLastName());
    ui->EmailLE->setText(user->getEmailAddr());
    ui->BirthDayLE->setText(user->getBirthDay());
    ui->ZodiacSignLE->setText(user->getZodiacSign());
}


QUrlQuery DeleteDialog::getQuery() {
    QUrlQuery url;

    url.addQueryItem("first_name", _currentUser->getFirstName().toLower());
    url.addQueryItem("last_name", _currentUser->getLastName().toLower());
    url.addQueryItem("email", _currentUser->getEmailAddr().toLower());
    url.addQueryItem("birthday", _currentUser->getBirthDay());
    url.addQueryItem("zodiac", _currentUser->getZodiacSign().toLower());

    return url;
}


void DeleteDialog::onBtnYesClicked() {
    QUrlQuery url = getQuery();
    btnYesClicked(url);
    close();
}
