#include "usercentralareaviewmodel.h"

#include "src/ui/components/user.h"
#include "src/ui/components/icon.h"
#include "src/ui/components/playlist.h"

#include <QPushButton>
#include <QPixmap>
#include <QFrame>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QScrollArea>

namespace ui {
namespace viewmodels {

UserCentralAreaViewModel::UserCentralAreaViewModel(int user_id, int guest_id, QWidget *parent)
    : QWidget(parent)
    , m_userId(user_id)
    , m_layout{new QVBoxLayout(this)}
    , m_user{new ui::components::User(user_id, guest_id, this)}
    , m_isFriend{false}
    , m_guestId{guest_id}
{
    // Create and configure UI elements
    QHBoxLayout *infoLayout = new QHBoxLayout();

    QPixmap musicPixmap(":/resources/wh-music.png");
    ui::components::InfoLabel *count_of_song = new ui::components::InfoLabel(musicPixmap, 6);
    QPixmap energyPixmap(":/resources/wh-energy.png");
    ui::components::InfoLabel *count_of_energy = new ui::components::InfoLabel(energyPixmap, 10);
    QPixmap friendPixmap(":/resources/wh-friends.png");
    int followcount = getFriendCount(m_userId);
    ui::components::InfoLabel *count_of_friend = new ui::components::InfoLabel(friendPixmap, followcount);

    infoLayout->addWidget(count_of_song);
    infoLayout->addWidget(count_of_energy);
    infoLayout->addWidget(count_of_friend);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    m_addFriendButton = new QPushButton(this);
    int followme = getFriendMeCount(m_userId);
    QLabel *followerButton = new QLabel(QString::number(followme) + " Following");
    followerButton->setStyleSheet("background-color: transparent; color: white;");
    buttonLayout->addWidget(m_addFriendButton);
    buttonLayout->addWidget(followerButton);
    buttonLayout->setAlignment(Qt::AlignRight);
    buttonLayout->setSpacing(30);

    connect(m_addFriendButton, &QPushButton::clicked, this, &UserCentralAreaViewModel::handleAddFriendButtonClick);

    updateAddFriendButton(); // Update button text and color


    QHBoxLayout *allInfoLayout = new QHBoxLayout();
    allInfoLayout->addLayout(infoLayout);
    allInfoLayout->addLayout(buttonLayout);

    // Add a horizontal line
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("background-color: #1a1a1a;");

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(m_user);
    mainLayout->addLayout(allInfoLayout);

    m_layout->addLayout(mainLayout);
    m_layout->addWidget(line); // Add the line below the components

    // Create the ParentWidget for the user's playlists
    ui::components::ParentWidget *playlistWidget = new ui::components::ParentWidget(user_id, false, this);

    // Create the scroll area for the user's playlists
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(playlistWidget);
    applyScrollAreaStyles(scrollArea);

    QLabel *playlistTitle = new QLabel("Public Playlists", this);
    playlistTitle->setStyleSheet("color: white; font-weight: bold; font-size: 26px; background-color: #212121;");
    m_layout->addWidget(playlistTitle);
    m_layout->addWidget(scrollArea); // Add the scroll area to the main layout

    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setStyleSheet("background-color: #212121; color: white;");
    this->setStyleSheet("QLabel { font-size: 14px; color: white; } ");

    setLayout(m_layout);
}

void UserCentralAreaViewModel::applyScrollAreaStyles(QScrollArea *scroll_area)
{
    scroll_area->setStyleSheet(
        "QScrollArea { border: none; }"
        "QScrollBar::handle { background-color: black; }"
        "QScrollBar::handle:horizontal { background-color: #212121; }"
        "QScrollBar::handle:vertical { background-color: black; }"
        );
}

bool UserCentralAreaViewModel::addFriendToDatabase(int userId, int friendId)
{
    QSqlQuery query;
    query.prepare("INSERT INTO friends (user_id, friend_id) VALUES (:user_id, :friend_id)");
    query.bindValue(":user_id", friendId); // Reverse the order
    query.bindValue(":friend_id", userId);
    if (!query.exec()) {
        qDebug() << "Failed to add friend:" << query.lastError();
        return false;
    }
    return true;
}

bool UserCentralAreaViewModel::removeFriendFromDatabase(int userId, int friendId)
{
    QSqlQuery query;
    query.prepare("DELETE FROM friends WHERE user_id = :user_id AND friend_id = :friend_id");
    query.bindValue(":user_id", friendId); // Reverse the order
    query.bindValue(":friend_id", userId);
    if (!query.exec()) {
        qDebug() << "Failed to remove friend:" << query.lastError();
        return false;
    }
    return true;
}

bool UserCentralAreaViewModel::isFriend(int userId, int friendId)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM friends WHERE user_id = :user_id AND friend_id = :friend_id");
    query.bindValue(":user_id", friendId); // Reverse the order
    query.bindValue(":friend_id", userId);
    if (!query.exec()) {
        qDebug() << "Failed to check friendship status:" << query.lastError();
        return false;
    }
    if (query.next()) {
        return query.value(0).toInt() > 0;
    }
    return false;
}

void UserCentralAreaViewModel::updateAddFriendButton()
{
    m_isFriend = isFriend(m_userId, m_guestId);

    if (m_isFriend) {
        m_addFriendButton->setText("Unfollow");
        m_addFriendButton->setStyleSheet(
            "QPushButton {"
            "    background-color: red;"
            "    color: white;"
            "    padding: 5px;"
            "    font-size: 15px;"
            "    font-weight: bold;"
            "}"
            );
    } else {
        m_addFriendButton->setText("Follow");
        m_addFriendButton->setStyleSheet(
            "QPushButton {"
            "    background-color: green;"
            "    color: white;"
            "    padding: 5px;"
            "    font-size: 15px;"
            "    font-weight: bold;"
            "}"
            );
    }
}

void UserCentralAreaViewModel::handleAddFriendButtonClick()
{
    qDebug() << "user id" << m_userId << " guest id" << m_guestId;
    if (m_isFriend) {
        if (removeFriendFromDatabase(m_userId, m_guestId)) {
            updateAddFriendButton();
        }
    } else {
        if (addFriendToDatabase(m_userId, m_guestId)) {
            updateAddFriendButton();
        }
    }
}


int UserCentralAreaViewModel::getFriendCount(int userId)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) AS friend_count "
                  "FROM friends "
                  "WHERE user_id = :userId OR friend_id = :userId");
    query.bindValue(":userId", userId);

    if (query.exec()) {
        if (query.next()) {
            int friendCount = query.value("friend_count").toInt();
            qDebug() << "User ID:" << userId << "has" << friendCount << "friends.";
            return friendCount;
        } else {
            qDebug() << "No rows returned for User ID:" << userId;
        }
    } else {
        qDebug() << "Failed to execute query for User ID:" << userId << query.lastError().text();
    }
    return 0;
}


int UserCentralAreaViewModel::getFriendMeCount(int userId)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) AS follower_count "
                  "FROM friends "
                  "WHERE friend_id = :userId");
    query.bindValue(":userId", userId);

    if (query.exec()) {
        if (query.next()) {
            int followerCount = query.value("follower_count").toInt();
            qDebug() << "User ID:" << userId << "is followed by" << followerCount << "users.";
            return followerCount;
        } else {
            qDebug() << "No rows returned for User ID:" << userId;
        }
    } else {
        qDebug() << "Failed to execute query for User ID:" << userId << query.lastError().text();
    }
    return 0;

}

}
}
