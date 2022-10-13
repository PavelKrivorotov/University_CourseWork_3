#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include <QUrlQuery>

namespace Ui {
class FilterDialog;
}

class FilterDialog : public QDialog {
    Q_OBJECT

public:
    explicit FilterDialog(QWidget *parent = nullptr);
    ~FilterDialog();

    QString getLastName();

    QString getZodiacSign();

    QString getBirthDay();

    bool getStateLastName();

    bool getStateBirthDay();

    bool getStateZodiacSign();

    QUrlQuery getQuery();

private:
    Ui::FilterDialog *ui;

    QString _lastName;
    int     _indexZodiacSign;
    QDate   *_birthDay;

    bool _stateLastName;
    bool _stateBirthDay;
    bool _stateZodiacSign;

private slots:
    void onOkBtnClicked();

protected:
    void closeEvent(QCloseEvent *) override;
};

#endif // FILTERDIALOG_H
