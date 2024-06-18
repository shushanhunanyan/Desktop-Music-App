#ifndef NEWPLAYLIST_H
#define NEWPLAYLIST_H

#include "src/ui/components/icon.h"
#include "src/ui/components/new_playlist_create.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>


namespace ui {
namespace components {
/*
class AddPlaylist : public QWidget
{
    Q_OBJECT

public:
    explicit AddPlaylist(int userId, QWidget *parent = nullptr);
    ~AddPlaylist() = default;

signals:
    void newPlaylistCreated(const QString &img, int playlistId, const QString &playlistName);

private slots:
    void onAddPlaylistClicked();

private:
    bool insertNewPlaylistIntoDatabase(int userId, const QString& playlistName, int);
    ui::components::CreateIcon *m_addIcon;
    QHBoxLayout *m_layout;
    QLabel *m_new_playlist_lbl;
    QPushButton *m_button;
    int m_userId;  // Store the user ID
};*/
class AddPlaylist : public QWidget
{
    Q_OBJECT

public:
    explicit AddPlaylist(int userId, QWidget *parent = nullptr);

signals:
   // void newPlaylistCreated(const QString& iconPath, int playlistId, const QString& playlistName);

    void newPlaylistCreated(const QString &img, int playlistId, const QString &playlistName, bool isPublic);

private slots:
    void onAddPlaylistClicked();

private:
    bool insertNewPlaylistIntoDatabase(int userId, const QString& playlistName, int isPublic);

    QHBoxLayout *m_layout;
    QLabel *m_new_playlist_lbl;
    QPushButton *m_button;
    ui::components::CreateIcon *m_addIcon;
    int m_userId;
};

}
}
#endif // NEWPLAYLIST_H
