#include "chatmanager.h"


#include <QFile>
#include <QTextStream>

ChatWidget::ChatWidget(QWidget *parent)
    : QWidget(parent),
    m_layout(new QVBoxLayout(this)),
    m_usernameLabel(new QLabel(this)),
    m_chatHistory(new QTextEdit(this)),
    m_messageInput(new QLineEdit(this)),
    m_sendButton(new QPushButton("Send", this)),
    m_backButton(new QPushButton("Back", this)),
    m_socket(new QTcpSocket(this))
{
    m_chatHistory->setReadOnly(true);

    m_layout->addWidget(m_backButton);
    m_layout->addWidget(m_usernameLabel);
    m_layout->addWidget(m_chatHistory);
    m_layout->addWidget(m_messageInput);
    m_layout->addWidget(m_sendButton);

    setLayout(m_layout);

    connect(m_sendButton, &QPushButton::clicked, this, &ChatWidget::onSendButtonClicked);
    connect(m_backButton, &QPushButton::clicked, this, &ChatWidget::backButtonClicked);
    connect(m_socket, &QTcpSocket::readyRead, this, &ChatWidget::onReadyRead);

    setupSocket();

    // Load stylesheet
    applyStyleSheet(":/stylesheets/chat_style.qss");
}

void ChatWidget::applyStyleSheet(const QString &styleSheetPath) {
    QFile styleFile(styleSheetPath);
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream styleStream(&styleFile);
        QString styleSheet = styleStream.readAll();
        setStyleSheet(styleSheet);
        styleFile.close();
    } else {
        qDebug() << "Failed to open stylesheet file: " << styleSheetPath;
    }
}

void ChatWidget::setupSocket() {
    m_socket->connectToHost(QHostAddress("127.0.0.1"), 8080);
    if (!m_socket->waitForConnected(3000)) {
        qDebug() << "Error: " << m_socket->errorString();
    }
}

void ChatWidget::setUsername(const QString &username) {
    m_usernameLabel->setText("Chatting with: " + username);
}

void ChatWidget::appendMessage(const QString &message, bool isLocalUser) {
    if (isLocalUser) {
        m_chatHistory->append("<div align=\"right\">" + message + "</div>");
    } else {
        m_chatHistory->append(message);
    }
}

void ChatWidget::onSendButtonClicked() {
    const QString message = m_messageInput->text();
    if (!message.isEmpty()) {
        QString formattedMessage = "You: " + message;
        appendMessage(formattedMessage, true); // Message from local user
        m_socket->write(message.toUtf8());
        m_socket->flush();
        m_messageInput->clear();
    }
}

void ChatWidget::onReadyRead() {
    QByteArray data = m_socket->readAll();
    QString message = QString::fromUtf8(data);
    appendMessage(message, false);
}
