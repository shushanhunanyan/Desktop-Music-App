#include "addtoplaylistdialog.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>




AddToPlaylistDialog::AddToPlaylistDialog(int userId, int musicId, QWidget *parent)
    : QDialog(parent)
    , m_userId(userId)
    , m_musicId(musicId)
    , m_layout(new QVBoxLayout(this))
    , m_playlistComboBox(new QComboBox(this))
    , m_addButton(new QPushButton("Add to Playlist", this))
{
    QSqlDatabase db = DatabaseManager::instance()->database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open.";
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT playlist_id, name FROM playlists WHERE user_id = :userId");
    query.bindValue(":userId", userId);
    if (query.exec()) {
        while (query.next()) {
            int playlistId = query.value("playlist_id").toInt();
            QString playlistName = query.value("name").toString();
            m_playlistComboBox->addItem(playlistName, playlistId);
        }
    } else {
        qDebug() << "Failed to load playlists:" << query.lastError().text();
    }

    // Set up the layout
    m_layout->addWidget(m_playlistComboBox);
    m_layout->addWidget(m_addButton);
    setLayout(m_layout);

    connect(m_addButton, &QPushButton::clicked, this, &AddToPlaylistDialog::onAddButtonClicked);
}

void AddToPlaylistDialog::onAddButtonClicked()
{
    int playlistId = m_playlistComboBox->currentData().toInt();

    QSqlDatabase db = DatabaseManager::instance()->database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open.";
        return;
    }

    // Check if the song already exists in the playlist
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT COUNT(*) FROM playlist_songs WHERE playlist_id = :playlistId AND music_id = :musicId");
    checkQuery.bindValue(":playlistId", playlistId);
    checkQuery.bindValue(":musicId", m_musicId);
    if (!checkQuery.exec()) {
        qDebug() << "Error checking for existing song in playlist:" << checkQuery.lastError().text();
        return;
    }

    checkQuery.next();
    int count = checkQuery.value(0).toInt();
    if (count > 0) {
        qDebug() << "Song already exists in the playlist.";
        QMessageBox::information(this, "Info", "Song already exists in the playlist.");
        return;
    }

    // Insert the song into the playlist
    QSqlQuery query(db);
    query.prepare("INSERT INTO playlist_songs (playlist_id, music_id) VALUES (:playlistId, :musicId)");
    query.bindValue(":playlistId", playlistId);
    query.bindValue(":musicId", m_musicId);

    if (query.exec()) {
        qDebug() << "Song added to playlist successfully.";
        accept();
    } else {
        qDebug() << "Failed to add song to playlist:" << query.lastError().text();
        qDebug() << "Executed query:" << query.executedQuery();
        reject();
    }
}
