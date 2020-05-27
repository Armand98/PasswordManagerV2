#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, QString login, QString password)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setStartValues(login, password);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setStartValues(QString login, QString password)
{
    QStringList comboBoxItemList;
    for(int i=6; i<=32; i++) {
        comboBoxItemList.append(QString::number(i));
    }

    ui->comboBoxPassLength->addItems(comboBoxItemList);
    ui->comboBoxPassLength->setCurrentIndex(6);
    ui->checkBoxUpperCaseLetters->setChecked(true);
    ui->checkBoxLowerCaseLetters->setChecked(true);
    ui->checkBoxDigits->setChecked(true);
    this->passwordSelection=false;

    ui->lineEditSite->setPlaceholderText("Enter site name");
    ui->lineEditSite->setAlignment(Qt::AlignCenter);
    ui->lineEditUsername->setPlaceholderText("Enter login");
    ui->lineEditUsername->setAlignment(Qt::AlignCenter);
    ui->lineEditPassword->setPlaceholderText("Enter password");
    ui->lineEditPassword->setAlignment(Qt::AlignCenter);

    ui->lineEditUrPassPassword->setEchoMode(QLineEdit::Password);
    ui->labelAddPassWarning->setVisible(false);

    myPassManager = new PasswordManager(login, password);
    myPassManager->loadDatasetListFromFile();

    updateListOfPasswords();
}

bool MainWindow::validateDataset(QString site, QString login, QString password)
{
    if(site.length() < 1) {
        ui->labelAddPassWarning->setText("Site must be at least 1 character long");
        ui->labelAddPassWarning->setVisible(true);
        return false;
    }

    if(login.length() < 2) {
        ui->labelAddPassWarning->setText("Login must be at least 2 characters long");
        ui->labelAddPassWarning->setVisible(true);
        return false;
    }

    if(password.length() < 6) {
        ui->labelAddPassWarning->setText("Password must be at least 6 characters long");
        ui->labelAddPassWarning->setVisible(true);
        return false;
    }


    for (int i=0; i<site.length(); i++) {
        if(site.at(i) == 32) {
            ui->labelAddPassWarning->setText("Site cannot contain whitespace characters");
            ui->labelAddPassWarning->setVisible(true);
            return false;
        }
    }

    for (int i=0; i<login.length(); i++) {
        if(login.at(i) == 32) {
            ui->labelAddPassWarning->setText("Login cannot contain whitespace characters");
            ui->labelAddPassWarning->setVisible(true);
            return false;
        }
    }

    for (int i=0; i<password.length(); i++) {
        if(password.at(i) == 32) {
            ui->labelAddPassWarning->setText("Password cannot contain whitespace characters");
            ui->labelAddPassWarning->setVisible(true);
            return false;
        }
    }

    return true;
}


void MainWindow::updateListOfPasswords()
{
    for(int i=0; i<myPassManager->getDatasetListSize(); i++) {
        DataSet tempDataset = myPassManager->getDatasetListAt(i);
        ui->comboBoxUrPassSite->addItem(tempDataset.getSite());
    }
}

void MainWindow::addItemToComboBox(QString site)
{
    ui->comboBoxUrPassSite->addItem(site);
}

void MainWindow::on_btnGeneratePassword_clicked()
{
    bool lowerCaseLettersCheckBoxValue = ui->checkBoxLowerCaseLetters->isChecked();
    bool upperCaseLettersCheckBoxValue = ui->checkBoxUpperCaseLetters->isChecked();
    bool digitsCheckBoxValue = ui->checkBoxDigits->isChecked();
    bool specialCharsCheckBoxValue = ui->checkBoxSymbols->isChecked();
    int passwordLength = ui->comboBoxPassLength->currentText().toInt();

    QString generatedPassword = PasswordGenerator::generatePassword(lowerCaseLettersCheckBoxValue, upperCaseLettersCheckBoxValue,
                                        digitsCheckBoxValue, specialCharsCheckBoxValue, passwordLength);

    ui->lineEditPassword->setText(generatedPassword);
}

void MainWindow::on_btnSaveNewPassword_clicked()
{
    ui->labelAddPassWarning->setVisible(false);
    QString site = ui->lineEditSite->text();
    QString login = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();

    if(validateDataset(site, login, password)) {
        if(!myPassManager->isSiteAlreadyUsed(site)) {

            ui->lineEditSite->setText("");
            ui->lineEditUsername->setText("");
            ui->lineEditPassword->setText("");

            DataSet newDataset(site, login, password, 0);
            myPassManager->addNewDatasetToTheList(newDataset);
            addItemToComboBox(newDataset.getSite());
        } else {
            ui->labelAddPassWarning->setText("This name of site is already used");
            ui->labelAddPassWarning->setVisible(true);
        }
    }
}

void MainWindow::on_comboBoxUrPassSite_currentIndexChanged(const QString &arg1)
{
    int index = ui->comboBoxUrPassSite->currentIndex();
    if(index >= 0) {
        DataSet *item = myPassManager->getDatasetItem(arg1);
        ui->lineEditUrPassUsername->setText(item->getLogin());
        ui->lineEditUrPassPassword->setText(item->getPassword());

        if(passwordSelection) {
            ui->lineEditUrPassPassword->setEchoMode(QLineEdit::Password);
            ui->btnPasswordDisplayMode->setText("Show password");
            passwordSelection = !passwordSelection;
        }
    }
}

void MainWindow::on_btnDeleteDataset_clicked()
{
    if(myPassManager->getDatasetListSize() > 0) {
        QString site = ui->comboBoxUrPassSite->currentText();
        int index = ui->comboBoxUrPassSite->currentIndex();
        myPassManager->deleteDatasetElement(site);
        ui->lineEditUrPassUsername->setText("");
        ui->lineEditUrPassPassword->setText("");
        ui->comboBoxUrPassSite->removeItem(index);
        QMessageBox::information(this, "Info", site + " was deleted.", QMessageBox::Ok);
    } else {
        QMessageBox::information(this, "Info", "There's nothing to delete.", QMessageBox::Ok);
    }
}

void MainWindow::on_btnEditDataset_clicked()
{
    if(myPassManager->getDatasetListSize() > 0) {
        QString site = ui->comboBoxUrPassSite->currentText();
        QString login = ui->lineEditUrPassUsername->text();
        QString password = ui->lineEditUrPassPassword->text();
        myPassManager->updateDatasetElement(site, login, password);
        QMessageBox::information(this, "Info", site + " was edited.", QMessageBox::Ok);
    } else {
        QMessageBox::information(this, "Info", "There's nothing to edit.", QMessageBox::Ok);
    }
}

void MainWindow::on_btnCopyPasswordToClipboard_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    QString password = ui->lineEditUrPassPassword->text();
    clipboard->setText(password);
    QString site = ui->comboBoxUrPassSite->currentText();
    myPassManager->updateDatasetElement(site);
}

void MainWindow::on_btnPasswordDisplayMode_clicked()
{
    passwordSelection = !passwordSelection;
    if(passwordSelection) {
        ui->lineEditUrPassPassword->setEchoMode(QLineEdit::Normal);
        ui->btnPasswordDisplayMode->setText("Hide password");
    } else {
        ui->lineEditUrPassPassword->setEchoMode(QLineEdit::Password);
        ui->btnPasswordDisplayMode->setText("Show password");
    }
}

void MainWindow::on_btnDeleteAllPasswords_clicked()
{
    if(myPassManager->getDatasetListSize() > 0) {
        QMessageBox::StandardButton reply = QMessageBox::warning(this, "Data wipe", "Delete all data?", QMessageBox::Yes | QMessageBox::No);

        if(reply == QMessageBox::Yes) {
            myPassManager->deleteAllData();
            ui->lineEditUrPassUsername->setText("");
            ui->lineEditUrPassPassword->setText("");
            ui->comboBoxUrPassSite->clear();
            QMessageBox::information(this, "Info", "All data were wiped.", QMessageBox::Ok);
        }
    } else {
        QMessageBox::information(this, "Info", "There's nothing to delete.", QMessageBox::Ok);
    }
}
