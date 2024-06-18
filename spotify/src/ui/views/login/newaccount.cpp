#include "newaccount.h"


NewAccount::NewAccount()
    : m_layout (new QHBoxLayout(this)),
    m_title(new QLabel("Sign up to start listening", this)),
    m_username(new QLineEdit(this)),
    m_password(new QLineEdit(this)),
    m_signin(new QPushButton("Sign Up", this)),
    m_generate_pass(new QPushButton(QIcon(":resources/generate_pass.png"), "", this))
{
    resize(800, 700);
    _setComponents();
    _setWidgets();

    connect(m_generate_pass, &QPushButton::clicked, this, &NewAccount::onGeneratePasswordClicked);
    connect(m_signin, &QPushButton::clicked, this, &NewAccount::onSignUpClicked);
    connect(this, &NewAccount::signUpSuccessful, this, &NewAccount::onSignUpSuccessful);
}

void NewAccount::_setComponents()
{
    m_title->setStyleSheet("QLabel { color: #dbdbbb;"
                                " font-size: 40px; font-family: serif; margin-bottom: 35px; }");


    m_password->setFixedWidth(300);
    m_username->setFixedWidth(300);
    m_username->setFixedHeight(40);
    m_password->setFixedHeight(40);
    m_username->setStyleSheet("QLineEdit { background-color: transparent; color: #dbdbbb; border: white }"
                              "QLineEdit:hover { border: 0.5px solid white; }");
    m_password->setStyleSheet("QLineEdit { background-color: transparent; color: #dbdbbb; border: white }"
                              "QLineEdit:hover { border: 0.5px solid #e6dbd5; }");

    m_generate_pass->setStyleSheet("QPushButton { background-color: transparent;  border: none}");
    m_username->setPlaceholderText("Username");
    m_password->setPlaceholderText("Password");
  //  m_password->setEchoMode(QLineEdit::Password);

    m_generate_pass->setIconSize(QSize(20, 20));
    m_generate_pass->setFixedSize(40, 40);
    m_signin->setFixedWidth(350);
    m_signin->setFixedHeight(45);
    m_signin->setStyleSheet("QPushButton { background-color: #dbdbbb; border-radius: 20px; }"
                             "QPushButton:hover { background-color: white; }");


    setStyleSheet("background-color: #817c6a");
}


void NewAccount::_setWidgets()
{
    QVBoxLayout *left_layout = new QVBoxLayout();
    left_layout->addWidget(m_title);

    QHBoxLayout *username_layout = new QHBoxLayout();
    username_layout->addWidget(m_username);

    QHBoxLayout *password_layout = new QHBoxLayout();
    password_layout->addWidget(m_password);
    password_layout->addWidget(m_generate_pass);

    username_layout->setAlignment(Qt::AlignLeft);
    password_layout->setAlignment(Qt::AlignLeft);

    left_layout->addLayout(username_layout);
    left_layout->addLayout(password_layout);
    left_layout->addWidget(m_signin);
    left_layout->setSpacing(20);

    m_layout->addLayout(left_layout);
    m_layout->setAlignment(Qt::AlignCenter);
    m_layout->setContentsMargins(60, 10, 0, 30);
}

void NewAccount::onGeneratePasswordClicked()
{
    Generator *generate_pass = new Generator;
    std::string password = generate_pass->GeneratePassword();

    QString qPassword = QString::fromStdString(password);

    delete generate_pass;

    m_password->setText(qPassword);
}


void NewAccount::onSignUpClicked()
{
    DatabaseManager* db = DatabaseManager::instance();

    if (!db->database().isOpen()) {
        qDebug() << "Error: Failed to open database";
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username");
    query.bindValue(":username", m_username->text());

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QMessageBox::warning(this, "Username not available", "This username is already taken. Please choose another one.");
        return;
    }

    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", m_username->text());
    query.bindValue(":password", m_password->text());

    if (!query.exec()) {
        qDebug() << "Error executing insert query:" << query.lastError().text();
        return;
    }

    int id = query.value(0).toInt();

    QMessageBox::information(this, "Sign Up Successful", "You have successfully signed up!");

    emit signUpSuccessful(id);
}

void NewAccount::onSignUpSuccessful(int userId)
{
    this->close();

    MainWindow *mainWindow = new MainWindow(userId);
    mainWindow->show();
}

NewAccount::~NewAccount()
{
    delete m_layout;
    delete m_title;
    delete m_username;
    delete m_password;
    delete m_signin;
    delete m_generate_pass;
}
