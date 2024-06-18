#include "newplaylist.h"


namespace ui {
namespace components {



AddPlaylist::AddPlaylist(int userId, QWidget *parent)
    : QWidget(parent)
    , m_layout(new QHBoxLayout())
    , m_new_playlist_lbl(new QLabel("New Playlist", this))
    , m_button(new QPushButton(this))
    , m_userId(userId)
{
    QPixmap iconPixmap(":/resources/wh-add.png");
    m_addIcon = new ui::components::CreateIcon(iconPixmap, 30, this);

    m_layout->addWidget(m_addIcon);
    m_layout->addWidget(m_new_playlist_lbl);
    m_layout->setContentsMargins(20, 5, 5, 5);
    m_layout->setSpacing(8);

    QWidget *buttonContent = new QWidget(this);
    buttonContent->setLayout(m_layout);

    QHBoxLayout *buttonLayout = new QHBoxLayout(m_button);
    buttonLayout->addWidget(buttonContent);
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    m_button->setLayout(buttonLayout);

    m_button->setStyleSheet(
        "QPushButton {"
        "    border: none;"
        "    background-color: #f9f9f9;"
        "    padding: 10px;"
        "    border-radius: 10px;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background-color: #e0e0e0;"
        "}"
        "QLabel {"
        "    margin-left: 5px;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}"
        );

    m_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_button->setMinimumHeight(50);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(m_button);
    mainLayout->setContentsMargins(1, 0, 0, 0);
    setLayout(mainLayout);

    connect(m_button, &QPushButton::clicked, this, &AddPlaylist::onAddPlaylistClicked);
}
/*
void AddPlaylist::onAddPlaylistClicked()
{
    NewPlaylistDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString playlistName = dialog.getPlaylistName();
        int isPublic = dialog.isPublicPlaylist(); // Retrieve the value
        qDebug() << "Creating playlist:" << playlistName << "Public:" << isPublic;
        if (insertNewPlaylistIntoDatabase(m_userId, playlistName, isPublic)) {
            QSqlQuery query;
            if (query.exec("SELECT last_insert_rowid()")) {
                if (query.next()) {
                    int newPlaylistId = query.value(0).toInt();
                    emit newPlaylistCreated(":/resources/images/default_playlist.png", newPlaylistId, playlistName);
                } else {
                    qDebug() << "Failed to retrieve last insert ID.";
                }
            } else {
                qDebug() << "Failed to execute last_insert_rowid query:" << query.lastError().text();
            }
        } else {
            qDebug() << "Failed to create new playlist.";
        }
    } else {
        qDebug() << "Dialog was rejected";
    }
}*/
void AddPlaylist::onAddPlaylistClicked()
{
    NewPlaylistDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString playlistName = dialog.getPlaylistName();
        int isPublic = dialog.isPublicPlaylist(); // Retrieve the value
        qDebug() << "Creating playlist:" << playlistName << "Public:" << isPublic;
        if (insertNewPlaylistIntoDatabase(m_userId, playlistName, isPublic)) {
            QSqlQuery query;
            if (query.exec("SELECT last_insert_rowid()")) {
                if (query.next()) {
                    int newPlaylistId = query.value(0).toInt();
                    emit newPlaylistCreated(":/resources/images/default_playlist.png", newPlaylistId, playlistName, isPublic); // Emitting the signal with the new argument
                } else {
                    qDebug() << "Failed to retrieve last insert ID.";
                }
            } else {
                qDebug() << "Failed to execute last_insert_rowid query:" << query.lastError().text();
            }
        } else {
            qDebug() << "Failed to create new playlist.";
        }
    } else {
        qDebug() << "Dialog was rejected";
    }
}



bool AddPlaylist::insertNewPlaylistIntoDatabase(int userId, const QString& playlistName, int isPublic)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO playlists (user_id, name, is_public) VALUES (:userId, :name, :isPublic)");
    query.bindValue(":userId", userId);
    query.bindValue(":name", playlistName);
    query.bindValue(":isPublic", isPublic);
    if (!query.exec()) {
        qDebug() << "Failed to insert new playlist:" << query.lastError().text();
        return false;
    }
    return true;
}
} // namespace components
} // namespace ui
