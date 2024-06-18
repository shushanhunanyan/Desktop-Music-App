#include "left_sidebar_view.h"
#include "src/ui/components/album.h"
#include "src/core/Database/userdataaccess.h"
#include "src/ui/components/songinfo.h"
#include "src/ui/components/artist.h"
#include "src/ui/components/playlist.h"
#include "src/ui/components/newplaylist.h"

#include <QSqlQuery>

namespace ui {
namespace views {


LeftSidebarView::LeftSidebarView(int userId, QWidget *parent)
    : QWidget(parent)
    , m_layout(new QVBoxLayout(this))
    , m_user(new ui::components::User(userId, userId, this))
    , m_tabWidget(new QTabWidget(this))
    , m_userId(userId)
{
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

    m_layout->addWidget(m_user);
    m_layout->addLayout(infoLayout);
    m_layout->addWidget(m_tabWidget);

    setupPlaylistsTab(userId);
    setupArtistsTab(userId);
    setupSongsTab(userId);

    m_tabWidget->setStyleSheet(
        "QTabWidget::pane { "
        "    border-top: 1px solid #e8e7e6;"
        "}"
        "QTabWidget::tab-bar {"
        "    left: 20px;"
        "}"
        "QTabBar::tab {"
        "    background: #f6f6f6;"
        "    color: #242424;"
        "    border: none;"
        "    border-bottom-color: #e8e7e6;"
        "    border-top-left-radius: 5px;"
        "    border-top-right-radius: 5px;"
        "    padding: 5px;"
        "}"
        "QTabBar::tab:selected, QTabBar::tab:hover {"
        "    background: #242424;"
        "    color: #e8e7e6;"
        "}"
        "QTabBar::tab:selected {"
        "    border-color: #131414;"
        "    border-bottom-color: #e8e7e6;"
        "}"
        "QTabBar::tab:!selected {"
        "    margin-top: 2px;"
        "}"
        );

    setAttribute(Qt::WA_StyledBackground, true);
    setLayout(m_layout);
    setStyleSheet("QLabel { font-size: 14px; color: white; } ");

}

void LeftSidebarView::addNewPlaylist(const QString &img, int playlistId, const QString &playlistName, bool isPublic)
{
    qDebug() << "Adding new playlist to sidebar:" << playlistName << "with ID:" << playlistId;
    QString iconPath = isPublic ? ":/resources/wh-padlock-public.png" : ":/resources/wh-lock-private.png";
    ui::components::Playlist *newPlaylist = new ui::components::Playlist(img, playlistId, 0, playlistName, iconPath, this);
    m_playlist_layout->insertWidget(m_playlist_layout->count() - 1, newPlaylist);
}

void LeftSidebarView::setupPlaylistsTab(int userId)
{
    QScrollArea *scroll_area = new QScrollArea();
    QWidget *playlist_widget = new QWidget();
    m_playlist_layout = new QVBoxLayout(playlist_widget);

    ui::components::AddPlaylist *addPlaylist = new ui::components::AddPlaylist(userId, this);
    connect(addPlaylist, &ui::components::AddPlaylist::newPlaylistCreated, this, &LeftSidebarView::addNewPlaylist);

    m_playlist_layout->setAlignment(Qt::AlignRight);

    ui::components::ParentWidget *playlist1 = new ui::components::ParentWidget(userId, true, this);
        connect(playlist1, &ui::components::ParentWidget::songClicked, this, &LeftSidebarView::handleSongClicked);
    m_playlist_layout->addWidget(playlist1);

    playlist_widget->setLayout(m_playlist_layout);
    m_playlist_layout->addWidget(addPlaylist);

    scroll_area->setWidget(playlist_widget);
    scroll_area->setWidgetResizable(true);
    scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_area->setAttribute(Qt::WA_StyledBackground, true);
    scroll_area->setStyleSheet("QScrollArea {border: none; }");

    m_tabWidget->addTab(scroll_area, "Playlists");
    applyScrollAreaStyles(scroll_area);
    playlist_widget->setStyleSheet("background-color: #212121;");
}
/*
void LeftSidebarView::setupSongsTab(int userId)
{
    QScrollArea *scroll_area = new QScrollArea();
    QWidget *song_widget = new QWidget();
    QVBoxLayout *song_layout = new QVBoxLayout(song_widget);

    for (int i = 1; i < 11; i++) {
        ui::components::Song *song = new ui::components::Song(i, this);
        song_layout->addWidget(song);
    }

    song_widget->setLayout(song_layout);

    scroll_area->setWidget(song_widget);
    scroll_area->setWidgetResizable(true);
    scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_tabWidget->addTab(scroll_area, "Songs");

    applyScrollAreaStyles(scroll_area);
    song_widget->setStyleSheet("background-color: #212121;");
}*/

void LeftSidebarView::handleSongClicked(int musicId)
{
    // Handle the song click here (e.g., update footer with song details)
    qDebug() << "Song with ID" << musicId << "clicked.";
    // Update footer or perform other actions
}

void LeftSidebarView::setupSongsTab(int userId)
{
    QScrollArea *scroll_area = new QScrollArea();
    QWidget *song_widget = new QWidget();
    QVBoxLayout *song_layout = new QVBoxLayout(song_widget);

    for (int i = 1; i < 11; i++) {
        ui::components::Song *song = new ui::components::Song(i, this);
        song_layout->addWidget(song);
        connect(song, &ui::components::Song::clicked, this, [=]() {
            emit songClicked(i); // Emit the songClicked signal with the song ID
        });
    }

    song_widget->setLayout(song_layout);

    scroll_area->setWidget(song_widget);
    scroll_area->setWidgetResizable(true);
    scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_tabWidget->addTab(scroll_area, "Songs");

    applyScrollAreaStyles(scroll_area);
    song_widget->setStyleSheet("background-color: #212121;");
}


void LeftSidebarView::setupArtistsTab(int userId)
{
    QScrollArea *scroll_area = new QScrollArea();
    QWidget *artist_widget = new QWidget();
    QVBoxLayout *artist_layout = new QVBoxLayout(artist_widget);

    for (int i = 37; i < 43; i++) {
        ui::components::Artist *artist = new ui::components::Artist(i, this);
        artist_layout->addWidget(artist);
    }

    artist_widget->setLayout(artist_layout);

    scroll_area->setWidget(artist_widget);
    scroll_area->setWidgetResizable(true);
    scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_tabWidget->addTab(scroll_area, "Artists");

    applyScrollAreaStyles(scroll_area);
    artist_widget->setStyleSheet("background-color: #212121;");
}

void LeftSidebarView::applyScrollAreaStyles(QScrollArea *scroll_area)
{
    scroll_area->setStyleSheet(
        "QScrollArea { border: none; }"
        "QScrollBar::handle { background-color: black; }"
        "QScrollBar::handle:horizontal { background-color: black; }"
        "QScrollBar::handle:vertical { background-color: black; }"
        );
}

int LeftSidebarView::getFriendCount(int userId)
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

} // namespace views
} // namespace ui
