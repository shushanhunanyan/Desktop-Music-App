#include "footer_components.h"


namespace ui
{
namespace components
{


/*
LeftSide::LeftSide(int id, QWidget *parent)
    : QWidget(parent), m_userId(id)
{
    sendToFriendComboBox = new QComboBox();
    sendToFriendComboBox->addItem("Send To a Friend...");
    sendToFriendComboBox->setStyleSheet(
        "QComboBox { background-color: transparent; border: 1px solid black; }"
        "QComboBox QAbstractItemView { background-color: #212121; color: white; }"
        "QComboBox::drop-down { background-color: transparent; border: none; }"
        );
    songName = new QLabel("  ");
    playButton = new QPushButton(QIcon(":/play.png"), "");
    playButton->setStyleSheet("background-color: transparent; border: none;");

    QHBoxLayout *nextTitle = new QHBoxLayout();
    nextTitle->addWidget(songName);
    nextTitle->addWidget(playButton);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(sendToFriendComboBox);
    layout->addLayout(nextTitle);

    setLayout(layout);

    loadFriends(m_userId);
}

LeftSide::~LeftSide()
{
}

void LeftSide::loadFriends(int userId) {
    QSqlQuery query;
    query.prepare("SELECT u.id, u.username FROM users u "
                  "JOIN friends f ON u.id = f.friend_id WHERE f.user_id = :userId");
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Failed to query friends:" << query.lastError();
        return;
    }

    while (query.next()) {
        int friendId = query.value(0).toInt();
        QString username = query.value(1).toString();
        sendToFriendComboBox->addItem(username, friendId);
    }
}*/
LeftSide::LeftSide(int id, QWidget *parent)
    : QWidget(parent), m_userId(id)
{
    sendToFriendComboBox = new QComboBox();
    sendToFriendComboBox->addItem("Send To a Friend...");
  /*  sendToFriendComboBox->setStyleSheet(
        "QComboBox { background-color: transparent; border: 1px solid black; }"
        "QComboBox QAbstractItemView { background-color: #212121; color: white; }"
        "QComboBox::drop-down { background-color: transparent; border: none; }"
        );*/
    sendToFriendComboBox->setStyleSheet(
        "QComboBox { background-color: transparent; border: 1px solid black; }"
        "QComboBox QAbstractItemView { background-color: black color: black; }"
        "QComboBox::drop-down { background-color: transparent; border: none; }"
        );

    sendToFriendComboBox->setStyleSheet("color: black");
    songName = new QLabel(" "); // Set the song name dynamically as needed
    playButton = new QPushButton(QIcon(":/play.png"), "");
    playButton->setStyleSheet("background-color: transparent; border: none;");

   // QPushButton *sendButton = new QPushButton("Send");
   // connect(sendButton, &QPushButton::clicked, this, &LeftSide::onSendButtonClicked);

    QHBoxLayout *nextTitle = new QHBoxLayout();
    nextTitle->addWidget(songName);
    nextTitle->addWidget(playButton);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(sendToFriendComboBox);
    layout->addLayout(nextTitle);
  //  layout->addWidget(sendButton);

    setLayout(layout);

    loadFriends(m_userId);
}

LeftSide::~LeftSide() {
}

void LeftSide::loadFriends(int userId) {
    QSqlQuery query;
    query.prepare("SELECT u.id, u.username FROM users u "
                  "JOIN friends f ON u.id = f.friend_id WHERE f.user_id = :userId");
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Failed to query friends:" << query.lastError();
        return;
    }

    while (query.next()) {
        int friendId = query.value(0).toInt();
        QString username = query.value(1).toString();
        sendToFriendComboBox->addItem(username, friendId);
    }
}

void LeftSide::onSendButtonClicked() {
    int friendId = sendToFriendComboBox->currentData().toInt();
    QString song = songName->text();

    if (friendId != 0) {
        emit sendSongToFriend(friendId, song);
    }
}


} // namespace components
} // namespace ui
