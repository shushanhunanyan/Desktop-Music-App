#ifndef CHATMANAGER_H
#define CHATMANAGER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>

/*
class ChatWidget : public QWidget {
    Q_OBJECT

public:
    ChatWidget(QWidget *parent = nullptr);
    void setUsername(const QString &username);
    void appendMessage(const QString &message);

signals:
    void sendMessage(const QString &message);
    void backButtonClicked();

private slots:
    void onSendButtonClicked();
    void onReadyRead();

private:
    QVBoxLayout *m_layout;
    QLabel *m_usernameLabel;
    QTextEdit *m_chatHistory;
    QLineEdit *m_messageInput;
    QPushButton *m_sendButton;
    QPushButton *m_backButton;
    QTcpSocket *m_socket;

    void setupSocket();
};
*/

class ChatWidget : public QWidget {
    Q_OBJECT

public:
    ChatWidget(QWidget *parent = nullptr);

    void setUsername(const QString &username);
    void appendMessage(const QString &message, bool);
    void applyStyleSheet(const QString &styleSheetPath);

signals:
    void sendMessage(const QString &message);
    void backButtonClicked(); // Add this signal

private slots:
    void onSendButtonClicked();
    void onReadyRead();

private:
    void setupSocket();

    QVBoxLayout *m_layout;
    QLabel *m_usernameLabel;
    QTextEdit *m_chatHistory;
    QLineEdit *m_messageInput;
    QPushButton *m_sendButton;
    QPushButton *m_backButton;
    QTcpSocket *m_socket;
};


#endif // CHATMANAGER_H
