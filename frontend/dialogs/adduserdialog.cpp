#include "adduserdialog.h"
#include "ui_adduserdialog.h"

#include <QJsonObject>
#include <QJsonDocument>


AddUserDialog::AddUserDialog(QWidget *parent): QDialog(parent), ui(new Ui::AddUserDialog){
    ui->setupUi(this);

    _defaultBirthDay = new QDate();

    _defaultFirstName = ui->FirstNameLE->text();
    _defaultLastName = ui->LastNameLE->text();
    _defaultEmailAddr = ui->EmailLE->text();
    *_defaultBirthDay = ui->BirthDayDE->date();

    connect(ui->AddpBtn, &QPushButton::clicked, this, &AddUserDialog::onAddBtnClicked);
    connect(ui->CencelBtn, &QPushButton::clicked, this, &AddUserDialog::close);
}


AddUserDialog::~AddUserDialog(){
    delete ui;
    delete _defaultBirthDay;
}


void AddUserDialog::closeEvent(QCloseEvent *){
    ui->FirstNameLE->setText(_defaultFirstName);
    ui->LastNameLE->setText(_defaultLastName);
    ui->EmailLE->setText(_defaultEmailAddr);
    ui->BirthDayDE->setDate(*_defaultBirthDay);
}


QByteArray AddUserDialog::getData() {
    QJsonObject json;

    json.insert("first_name", ui->FirstNameLE->text().toLower());
    json.insert("last_name", ui->LastNameLE->text().toLower());
    json.insert("email", ui->EmailLE->text().toLower());
    json.insert("birthday", ui->BirthDayDE->date().toString("yyyy-MM-dd"));

    return QJsonDocument(json).toJson(QJsonDocument::Compact);
}


void AddUserDialog::onAddBtnClicked() {
    QByteArray data = getData();
    btnAddClicked(data);

    close();
}

