#ifndef NEWACCOUNT_H
#define NEWACCOUNT_H

#include "generator.h"
#include "src/app/main_window.h"
#include "src/core/Database/databasemanager.h"


#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QtSql>
#include <QMessageBox>


class NewAccount : public QWidget
{
    Q_OBJECT

public:
    NewAccount();
    ~NewAccount();
private:
    void _setComponents();
    void _setWidgets();

signals:
    void signUpSuccessful(int id);

private slots:
    void onGeneratePasswordClicked();
    void onSignUpClicked();
    void onSignUpSuccessful(int);

private:
    QHBoxLayout *m_layout;
    QLabel *m_title;
    QLineEdit *m_username;
    QLineEdit *m_password;
    QPushButton *m_signin;
    QPushButton *m_generate_pass;
};

#endif // NEWACCOUNT_H
