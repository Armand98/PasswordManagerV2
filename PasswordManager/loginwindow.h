#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include "register.h"
#include "mainwindow.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    bool validateRegisterData(QString login, QString password);
    void setWarningsVisibility(bool showWarnings);


private slots:

    void on_btnLogIn_clicked();

    void on_btnRegister_clicked();

    void on_btnInfo_clicked();

private:
    Ui::LoginWindow *ui;
    MainWindow *mainWindow;
};

#endif // LOGINWINDOW_H
