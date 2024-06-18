#include "playlist.h"
#include "src/ui/components/new_playlist_create.h"
#include "src/ui/components/clickablelabel.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QPixmap>
#include <QDebug>
#include <QSqlError>

namespace ui {
namespace components {


ParentWidget::ParentWidget(int userId, bool showpalllaylist, QWidget *parent)
    : QWidget(parent)
    , m_playlist_layout(new QVBoxLayout(this))
    , m_userId(userId)
{
    QWidget *playlist_widget = new QWidget(this);
    playlist_widget->setLayout(m_playlist_layout);

    loadPlaylists(showpalllaylist);

    QVBoxLayout *main_layout = new QVBoxLayout(this);

    // Create and configure the back button
    m_backButton = new QPushButton("Back", this);
    m_backButton->setVisible(false); // Hide the button initially
    m_backButton->setStyleSheet("color: white;");

    // Create a horizontal layout for the back button
    QHBoxLayout *back_button_layout = new QHBoxLayout();
    back_button_layout->addWidget(m_backButton);
    back_button_layout->addStretch(); // Add a stretch to push the button to the left

    // Add the horizontal layout to the main layout
    main_layout->addLayout(back_button_layout);
    main_layout->addWidget(playlist_widget);

    connect(m_backButton, &QPushButton::clicked, this, &ParentWidget::showPlaylists);

    setLayout(main_layout);

}


void ParentWidget::loadPublicPlaylists()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT playlist_id, name FROM playlists WHERE user_id = :userId AND is_public = 1");
    query.bindValue(":userId", m_userId);
    if (query.exec()) {
        while (query.next()) {
            int playlistId = query.value("playlist_id").toInt();
            QString playlistName = query.value("name").toString();
            int songCount = getSongCountForPlaylist(playlistId);
            ui::components::Playlist *playlist = new ui::components::Playlist(":/resources/images/playlist4.png", playlistId, songCount, playlistName, QString(), this);
            connect(playlist, &ui::components::Playlist::playlistClicked, this, &ParentWidget::loadSongsForPlaylist);
            m_playlist_layout->addWidget(playlist);
        }
    } else {
        qDebug() << "Failed to load public playlists:" << query.lastError().text();
    }
}


void ParentWidget::loadAllPlaylists()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT playlist_id, name, is_public FROM playlists WHERE user_id = :userId");
    query.bindValue(":userId", m_userId);
    if (query.exec()) {
        while (query.next()) {
            int playlistId = query.value("playlist_id").toInt();
            QString playlistName = query.value("name").toString();
            bool isPublic = query.value("is_public").toBool();
            int songCount = getSongCountForPlaylist(playlistId);
            QString iconPath = isPublic ? ":/resourceswh-padlock-public.png" : ":/resources/wh-lock-private.png";
            ui::components::Playlist *playlist = new ui::components::Playlist(":/resources/images/playlist4.png", playlistId, songCount, playlistName, iconPath, this);
            connect(playlist, &ui::components::Playlist::playlistClicked, this, &ParentWidget::loadSongsForPlaylist);
            m_playlist_layout->addWidget(playlist);
        }
    } else {
        qDebug() << "Failed to load playlists:" << query.lastError().text();
    }
}



QLabel* createStyledSongLabel(const QString& text, QWidget* parent) {
    QLabel* songLabel = new QLabel(text, parent);
    songLabel->setStyleSheet(
        "font-size: 15px;"
        "color: #d3d4d2;"
        "background-color: transparent;"
        "padding: 5px;"
        "border-radius: 5px;"
        "margin: 5px 0;"
        );
    return songLabel;
}

void ParentWidget::showPlaylists()
{
    m_backButton->setVisible(false); // Hide the back button
    clearLayout(m_playlist_layout);
    //loadPlaylists(); // Reload the playlists
    loadAllPlaylists();

}

int ParentWidget::getSongCountForPlaylist(int playlistId)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM playlist_songs WHERE playlist_id = :playlistId");
    query.bindValue(":playlistId", playlistId);

    if (query.exec()) {
        if (query.next()) {
            int count = query.value(0).toInt();
            qDebug() << "Playlist ID:" << playlistId << "Song Count:" << count;
            return count;
        } else {
            qDebug() << "No rows returned for Playlist ID:" << playlistId;
        }
    } else {
        qDebug() << "Failed to execute query for Playlist ID:" << playlistId << query.lastError().text();
    }
    return 0;
}

void ParentWidget::loadSongsForPlaylist(int playlistId)
{
    qDebug() << "Loading songs for playlist ID:" << playlistId;

    // Show the back button
    m_backButton->setVisible(true);

    // Clear the existing layout
    clearLayout(m_playlist_layout);

    // Query the database for songs in the selected playlist
    QSqlQuery query;
    query.prepare("SELECT music.title, music.artist FROM music INNER JOIN playlist_songs ON music.music_id = playlist_songs.music_id WHERE playlist_songs.playlist_id = :playlistId");
    query.bindValue(":playlistId", playlistId);

    if (query.exec()) {
        int songNumber = 1; // Initialize song number
        while (query.next()) {
            QString songTitle = query.value("title").toString();
            QString songArtist = query.value("artist").toString();
            QString songLabelText = QString::number(songNumber) + " " + songTitle + " - " + songArtist;
            QLabel *songLabel = createStyledSongLabel(songLabelText, this);
            m_playlist_layout->addWidget(songLabel);
            songNumber++;
        }
    } else {
        qDebug() << "Failed to load songs for playlist ID:" << playlistId << query.lastError().text();
    }
}
/*es es chgitem ova
void ParentWidget::loadSongsForPlaylist(int playlistId)
{
    qDebug() << "Loading songs for playlist ID:" << playlistId;

    // Show the back button
    m_backButton->setVisible(true);

    // Clear the existing layout
    clearLayout(m_playlist_layout);

    // Query the database for songs in the selected playlist
    QSqlQuery query;
    query.prepare("SELECT music.music_id, music.title, music.artist FROM music INNER JOIN playlist_songs ON music.music_id = playlist_songs.music_id WHERE playlist_songs.playlist_id = :playlistId");
    query.bindValue(":playlistId", playlistId);

    if (query.exec()) {
        int songNumber = 1; // Initialize song number
        while (query.next()) {
            int musicId = query.value("music_id").toInt();
            QString songTitle = query.value("title").toString();
            QString songArtist = query.value("artist").toString();
            QString songLabelText = QString::number(songNumber) + " " + songTitle + " - " + songArtist;
ClickableLabel *songLabel = new ClickableLabel(songLabelText, this->parentWidget());
            m_playlist_layout->addWidget(songLabel);
            connect(songLabel, &ClickableLabel::clicked, this, [musicId]() {
                emit songClicked(musicId);
            });
            songNumber++;
        }
    } else {
        qDebug() << "Failed to load songs for playlist ID:" << playlistId << query.lastError().text();
    }
}*/


void ParentWidget::clearLayout(QLayout *layout)
{
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
}


void ParentWidget::loadPlaylists(bool showall)
{
    clearLayout(m_playlist_layout);

    if (showall) {
        loadAllPlaylists();
    } else {
        loadPublicPlaylists();
    }
}


Playlist::Playlist(const QString& img, int playlistId, int songCount, const QString &playlistName, const QString &iconPath, QWidget *parent)
    : QWidget(parent)
    , m_layout(new QHBoxLayout(this))
    , m_text_layout(new QVBoxLayout())
    , m_img_lbl(new QLabel(this))
    , m_title_lbl(new QLabel(playlistName, this))
    , m_song_lbl(new QLabel(QString::number(songCount) + " Songs", this))
    , m_icon_lbl(nullptr)
    , m_playlistId(playlistId)
{
    QPixmap pixmap(img);
    m_img_lbl->setPixmap(pixmap);
    m_img_lbl->setFixedSize(90, 90);
    m_img_lbl->setScaledContents(true);
    m_img_lbl->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    if (!iconPath.isEmpty()) {
        m_icon_lbl = new QLabel(this);
        QPixmap iconPixmap(iconPath);
        m_icon_lbl->setPixmap(iconPixmap);
        m_icon_lbl->setFixedSize(16, 16);
        m_icon_lbl->setScaledContents(true);
        m_icon_lbl->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    }

    m_title_lbl->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    m_song_lbl->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    m_title_lbl->setStyleSheet("font-weight: bold; color: white");
    m_song_lbl->setStyleSheet("color: #828282");

    m_text_layout->addWidget(m_title_lbl);
    m_text_layout->addWidget(m_song_lbl);
    if (m_icon_lbl) {
        m_text_layout->addWidget(m_icon_lbl);
    }
    m_text_layout->setAlignment(Qt::AlignBaseline);

    m_layout->addWidget(m_img_lbl);
    m_layout->addLayout(m_text_layout);
    m_layout->setAlignment(Qt::AlignBaseline);
    m_img_lbl->setStyleSheet("border: 2px solid #444; background-color: #222;");

    setLayout(m_layout);
}

void Playlist::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit playlistClicked(m_playlistId);
}


} // namespace components
} // namespace ui



