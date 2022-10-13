#include "filterdialog.h"
#include "ui_filterdialog.h"


FilterDialog::FilterDialog(QWidget *parent) : QDialog(parent), ui(new Ui::FilterDialog){
    ui->setupUi(this);

    _birthDay = new QDate();

    _lastName = ui->LastNameLE->text();
    _indexZodiacSign = ui->ZodiacSignCB_2->currentIndex();
    *_birthDay = ui->BirthDayDE->date();

    _stateLastName = ui->LastNameCB->isChecked();
    _stateZodiacSign = ui->ZodiacSignCB->isChecked();
    _stateBirthDay = ui->BirthDayCB->isChecked();

    connect(ui->CancelBtn, &QPushButton::clicked, this, &FilterDialog::close);
    connect(ui->OkBtn, &QPushButton::clicked, this, &FilterDialog::onOkBtnClicked);
}


FilterDialog::~FilterDialog(){
    delete ui;
    delete _birthDay;
}


void FilterDialog::closeEvent(QCloseEvent *){
    ui->LastNameLE->setText(_lastName);
    ui->ZodiacSignCB_2->setCurrentIndex(_indexZodiacSign);
    ui->BirthDayDE->setDate(*_birthDay);

    ui->LastNameCB->setChecked(_stateLastName);
    ui->ZodiacSignCB->setChecked(_stateZodiacSign);
    ui->BirthDayCB->setChecked(_stateBirthDay);
}


QString FilterDialog::getLastName(){
    return _lastName;
}


QString FilterDialog::getZodiacSign(){
    return ui->ZodiacSignCB_2->itemText(_indexZodiacSign);
}


QString FilterDialog::getBirthDay(){
    return _birthDay->toString("dd-MM-yyyy");
}


bool FilterDialog::getStateLastName() {
    return _stateLastName;
}


bool FilterDialog::getStateBirthDay() {
    return _stateBirthDay;
}


bool FilterDialog::getStateZodiacSign() {
    return _stateZodiacSign;
}


QUrlQuery FilterDialog::getQuery() {
    QUrlQuery url;

    if (_stateLastName) { url.addQueryItem("last_name", _lastName.toLower()); }
    if (_stateBirthDay) { url.addQueryItem("birthday", _birthDay->toString("yyyy-MM-dd")); }

    if (_stateZodiacSign) {
        QString zodiacSign = ui->ZodiacSignCB_2->itemText(_indexZodiacSign);
        url.addQueryItem("zodiac", zodiacSign.toLower());
    }

    return url;
}


void FilterDialog::onOkBtnClicked(){
    if (ui->LastNameCB->isChecked() == 1) {
        _stateLastName = true;
        _lastName = ui->LastNameLE->text();
    }
    else { _stateLastName = false; }

    if (ui->ZodiacSignCB->isChecked() == 1) {
        _stateZodiacSign = true;
        _indexZodiacSign = ui->ZodiacSignCB_2->currentIndex();
    }
    else { _stateZodiacSign = false; }

    if (ui->BirthDayCB->isChecked() == 1) {
        _stateBirthDay = true;
        *_birthDay = ui->BirthDayDE->date();
    }
    else { _stateBirthDay = false; }

    close();
}

