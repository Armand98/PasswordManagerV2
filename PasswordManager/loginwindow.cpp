#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "login.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->lineEditLoginPassword->setEchoMode(QLineEdit::Password);
    ui->labelLoginWarning->setVisible(false);
    ui->lineEditLoginUsername->setPlaceholderText("Enter Login");
    ui->lineEditLoginUsername->setAlignment(Qt::AlignCenter);
    ui->lineEditLoginPassword->setPlaceholderText("Enter Password");
    ui->lineEditLoginPassword->setAlignment(Qt::AlignCenter);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_btnLogIn_clicked()
{
    ui->labelLoginWarning->setVisible(false);
    QString login = ui->lineEditLoginUsername->text();
    QString password = ui->lineEditLoginPassword->text();
    if(Login::authenticate(login, password)) {

        mainWindow = new MainWindow(this, login, password);
        mainWindow->setAttribute(Qt::WA_DeleteOnClose);
        mainWindow->show();
        this->hide();
    } else {
        ui->labelLoginWarning->setVisible(true);
        ui->labelLoginWarning->setText("Wrong login or password");
    }
}

void LoginWindow::on_btnRegister_clicked()
{
    ui->labelLoginWarning->setVisible(false);
    QString login = ui->lineEditLoginUsername->text();
    QString password = ui->lineEditLoginPassword->text();

    if(validateRegisterData(login, password)) {
        if(Register::accountNotUsed(login)) {
            if(Register::addNewAccount(login, password)) {
                ui->labelLoginWarning->setText("Account was created successfully");
                ui->labelLoginWarning->setVisible(true);
            }
        } else {
            ui->labelLoginWarning->setVisible(true);
            ui->labelLoginWarning->setText("Login is already used");
        }
    }
}

void LoginWindow::on_btnInfo_clicked()
{
    ProgramInfo info;
    info.setModal(true);
    info.exec();
}

bool LoginWindow::validateRegisterData(QString login, QString password)
{
    if(login.length() < 6) {
        ui->labelLoginWarning->setText("Login must be at least 6 characters long");
        ui->labelLoginWarning->setVisible(true);
        return false;
    }

    if(password.length() < 6) {
        ui->labelLoginWarning->setText("Password must be at least 6 characters long");
        ui->labelLoginWarning->setVisible(true);
        return false;
    }

    for (int i=0; i<login.length(); i++) {
        if(login.at(i) == 32) {
            ui->labelLoginWarning->setText("Login cannot contain whitespace characters");
            ui->labelLoginWarning->setVisible(true);
            return false;
        }
    }

    for (int i=0; i<password.length(); i++) {
        if(password.at(i) == 32) {
            ui->labelLoginWarning->setText("Password cannot contain whitespace characters");
            ui->labelLoginWarning->setVisible(true);
            return false;
        }
    }

    int lowerCaseLetters = 0;
    int upperCaseLetters = 0;
    int digits = 0;
    int specialCharacters = 0;
    int prohibitedCharacters = 0;

    for (int i=0; i<password.length(); i++) {
        // if password contains special characters based on ASCII codes
        if( ((password.at(i) >= 33) && (password.at(i) <= 47)) ||
            ((password.at(i) >= 58) && (password.at(i) <= 64)) ||
            ((password.at(i) >= 91) && (password.at(i) <= 96)) ||
            ((password.at(i) >= 123) && (password.at(i) <= 126))) {
            specialCharacters++;
        // digits
        } else if ((password.at(i) >= 48) && (password.at(i) <= 57)) {
            digits++;
        // upper case letters
        } else if ((password.at(i) >= 65) && (password.at(i) <= 90)) {
            upperCaseLetters++;
        // lower case letters
        } else if ((password.at(i) >= 96) && (password.at(i) <= 122)) {
            lowerCaseLetters++;
        } else {
            prohibitedCharacters++;
        }
    }

    if(prohibitedCharacters > 0) {
        ui->labelLoginWarning->setText("You cannot use this password. Try another.");
        ui->labelLoginWarning->setVisible(true);
        return false;
    }

    if((lowerCaseLetters == 0) || (upperCaseLetters == 0) || (digits == 0) || (specialCharacters == 0)) {
        ui->labelLoginWarning->setText("Your password must include at least one uppercase\nand lowercase letter, digit and special character.");
        ui->labelLoginWarning->setVisible(true);
        return false;
    }

    return true;
}
