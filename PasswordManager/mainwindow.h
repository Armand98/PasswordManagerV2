#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include "register.h"
#include "dataset.h"
#include "passwordgenerator.h"
#include "passwordmanager.h"
#include "programinfo.h"
#include <QClipboard>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, QString login="", QString password="");
    ~MainWindow();
    void setStartValues(QString login, QString password);
    void setWarningsVisibility(bool showWarnings);   
    bool validateDataset(QString site, QString login, QString password);
    void updateListOfPasswords();
    void addItemToComboBox(QString site);

private slots:

    void on_btnGeneratePassword_clicked();

    void on_btnSaveNewPassword_clicked();

    void on_comboBoxUrPassSite_currentIndexChanged(const QString &arg1);

    void on_btnDeleteDataset_clicked();

    void on_btnEditDataset_clicked();

    void on_btnCopyPasswordToClipboard_clicked();

    void on_btnPasswordDisplayMode_clicked();

    void on_btnDeleteAllPasswords_clicked();

private:
    Ui::MainWindow *ui;
    PasswordManager *myPassManager;
    bool passwordSelection;
};
#endif // MAINWINDOW_H
