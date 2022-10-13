#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>
#include <QUrl>

namespace Ui {
class AddUserDialog;
}

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserDialog(QWidget *parent = nullptr);
    ~AddUserDialog();

private:
    QByteArray getData();

private:
    Ui::AddUserDialog *ui;

    QString _defaultFirstName;
    QString _defaultLastName;
    QString _defaultEmailAddr;
    QDate *_defaultBirthDay;

private slots:
    void onAddBtnClicked();

signals:
    void btnAddClicked(QByteArray data, QUrl urlAddr = QUrl("http://127.0.0.1:8000/api/create-content/"));

protected:
    void closeEvent(QCloseEvent *) override;
};

#endif // ADDUSERDIALOG_H
