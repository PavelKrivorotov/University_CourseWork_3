#include "changedialog.h"
#include "ui_changedialog.h"

#include <QJsonObject>
#include <QJsonDocument>


ChangeDialog::ChangeDialog(QWidget *parent): QDialog(parent), ui(new Ui::ChangeDialog) {
    ui->setupUi(this);

    connect(ui->YespBtn, &QPushButton::clicked, this, &ChangeDialog::onBtnYesClicked);
    connect(ui->NopBtn, &QPushButton::clicked, this, &ChangeDialog::close);
}


ChangeDialog::~ChangeDialog() {
    delete ui;
}


void ChangeDialog::setUserData(User *user) {
    _currentUser = user;

    ui->FirstNameLE->setText(user->getFirstName());
    ui->LastNameLE->setText(user->getLastName());
    ui->EmailLE->setText(user->getEmailAddr());
    ui->BirthDayDE->setDate(QDate::fromString(user->getBirthDay(), "yyyy-MM-dd"));
    ui->ZodiacSignLE->setText(user->getZodiacSign());
}


QByteArray ChangeDialog::getData() {
    QJsonObject json;

    json.insert("email", ui->EmailLE->text());
    if (_currentUser->getFirstName() != ui->FirstNameLE->text()) {
        json.insert("first_name", ui->FirstNameLE->text().toLower());
    }

    if (_currentUser->getLastName() != ui->LastNameLE->text()) {
        json.insert("last_name", ui->LastNameLE->text().toLower());
    }

    if (_currentUser->getBirthDay() != ui->BirthDayDE->date().toString("yyyy-MM-dd")) {
        json.insert("birthday", ui->BirthDayDE->date().toString("yyyy-MM-dd"));
    }

    return QJsonDocument(json).toJson(QJsonDocument::Compact);
}



void ChangeDialog::onBtnYesClicked() {
    QByteArray data = getData();
    btnYesClicked(data);
    close();
}
