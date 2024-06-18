#include "src/ui/views/login/welcome.h"


Welcome::Welcome(QWidget *parent)
    : QWidget(parent),
    m_bgPic(new QPixmap(":/resources/images/bg_pic.jpeg")),
    m_layout (new QVBoxLayout(this)),
    m_titleLabel(new QLabel("WELCOME", this)),
    m_username(new QLineEdit(this)),
    m_password(new QLineEdit(this)),
    m_loginButton(new QPushButton("Log In", this)),
  //  m_changePass(new QLabel("Forgot password?", this)),
    m_newAccount(new QLabel("Create New Account", this))
{
    resize(650, 830);
    _setBgPic();
    _setComponents();
    _setWidgets();
    _setConnections();


    m_layout->setAlignment(Qt::AlignCenter);
}


void Welcome::_setBgPic()
{
    QPixmap overlay(":/resources/images/bg_pic.jpeg");

    if (overlay.isNull()) {
        qDebug() << "Failed to load background image!";
        return;
    }

    overlay.fill(QColor(10, 0, 0, 110));
    *m_bgPic = m_bgPic->scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QPainter painter(m_bgPic);
    painter.drawPixmap(0, 0, overlay);

    QPalette palette;
    palette.setBrush(QPalette::Window, *m_bgPic);
    setPalette(palette);

}

void Welcome::_setComponents()
{
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet("QLabel { color: #dbdbbb;"
                                " font-size: 40px; font-family: serif; margin-bottom: 35px; }");

//    m_changePass->setAlignment(Qt::AlignRight);
//    m_changePass->setStyleSheet("QLabel { color: #dbdbbb; font-size: 17px; text-decoration: underline; }"
   //                             "QLabel:hover { text-decoration: underline; color: white }");

    m_newAccount->setAlignment(Qt::AlignCenter);
    m_newAccount->setStyleSheet("QLabel { color: #dbdbbb; font-size: 25px;  margin-top: 60px; font-family: serif; }"
                                "QLabel:hover { text-decoration: underline; color: white }");

    m_username->setFixedWidth(350);
    m_password->setFixedWidth(350);
    m_username->setFixedHeight(40);
    m_password->setFixedHeight(40);
    m_username->setStyleSheet("QLineEdit { background-color: transparent; color: white; border: white }"
                               "QLineEdit:hover { border: 0.5px solid #e6dbd5; }");
    m_password->setStyleSheet("QLineEdit { background-color: transparent; color: white; border: white }"
                              "QLineEdit:hover { border: 0.5px solid #e6dbd5; }");

    m_loginButton->setFixedWidth(350);
    m_loginButton->setFixedHeight(45);
    m_loginButton->setStyleSheet("QPushButton { background-color: #ced3b1; border-radius: 20px; } "
                                 "QPushButton:hover { background-color: #dbdbbb; }");


    m_username->setPlaceholderText("Username");
    m_password->setPlaceholderText("Password");
    m_password->setEchoMode(QLineEdit::Password);

}

void Welcome::_setWidgets()
{
    QVBoxLayout *name_pass = new QVBoxLayout(this);
    name_pass->addWidget(m_username);
    name_pass->addWidget(m_password);
    name_pass->setContentsMargins(0, 20, 0, 30);

    m_layout->addWidget(m_titleLabel);
    m_layout->addLayout(name_pass);
    m_layout->addWidget(m_loginButton);
//    m_layout->addWidget(m_changePass);
    m_layout->addWidget(m_newAccount);

    m_newAccount->installEventFilter(this);
}


void Welcome::_setConnections()
{
    connect(m_loginButton, &QPushButton::clicked, this, &Welcome::onLoginClicked);
 //   connect(m_changePass, &QLabel::clicked, this, &Welcome::onForgotPassClicked);
 //   connect(m_newAccount, &QLabel::clicked, this, &Welcome::onCreateAccountClicked);
}

bool Welcome::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_newAccount && event->type() == QEvent::MouseButtonPress)
    {
        onCreateAccountClicked();
        return true;
    }
    return false;
}

void Welcome::onLoginClicked()
{
    DatabaseManager* dbManager = DatabaseManager::instance();

    if (!dbManager->database().isOpen()) {
        QMessageBox::critical(this, "Error", "Failed to connect to the database.");
        return;
    }

    QSqlQuery query(dbManager->database());
    query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", m_username->text());
    query.bindValue(":password", m_password->text());

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to execute the query.");
        return;
    }

    if (query.next()) {
        int userId = query.value("id").toInt();
        bool isAdmin = query.value("is_admin").toBool();

        if (isAdmin) {
            AdminWindow *adminWindow = new AdminWindow();
            adminWindow->show();
        } else {
            MainWindow *mainWindow = new MainWindow(userId);
            mainWindow->show();
        }

        this->close();
    } else {
        QMessageBox::warning(this, "Login Failed", "Incorrect username or password. Please try again.");
    }
}

void Welcome::onCreateAccountClicked()
{
    this->hide();

    NewAccount *createAccountWindow = new NewAccount();
    createAccountWindow->show();
}

void Welcome::onForgotPassClicked()
{

}

Welcome::~Welcome()
{
    delete m_bgPic;
    delete m_layout;
    delete m_titleLabel;
    delete m_username;
    delete m_password;
    delete m_loginButton;
 //   delete m_changePass;
    delete m_newAccount;
}
