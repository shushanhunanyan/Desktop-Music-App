#ifndef WELCOME_H
#define WELCOME_H

#include "newaccount.h"
#include "src/app/main_window.h"
#include "src/ui/views/admin/adminwindow.h"
#include "src/core/Database/databasemanager.h"

#include <QWidget>
#include <QPixmap>
#include <QDebug>
#include <QPalette>
#include <QPainter>
#include <QColor>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QEvent>
#include <QSql>

class Welcome : public QWidget
{
    Q_OBJECT

public:
    Welcome(QWidget *parent = nullptr);
    ~Welcome();

private:
    void _setBgPic();
    void _setComponents();
    void _setWidgets();
    void _setConnections();

private slots:
    bool eventFilter(QObject*, QEvent*);

    void onLoginClicked();
    void onCreateAccountClicked();
    void onForgotPassClicked();

private:
    QPixmap *m_bgPic;
    QVBoxLayout *m_layout;
    QLabel *m_titleLabel;
    QLineEdit *m_username;
    QLineEdit *m_password;
    QPushButton *m_loginButton;
 //   QLabel *m_changePass;
    QLabel *m_newAccount;
};

#endif // WELCOME_H
