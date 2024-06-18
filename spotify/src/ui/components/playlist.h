#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>

#include "src/ui/views/footer/footer_view.h"

namespace ui {
namespace components {


class ParentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ParentWidget(int userId, bool, QWidget *parent = nullptr);

private slots:
    void loadSongsForPlaylist(int playlistId);
    void showPlaylists();

signals:
    void songClicked(int musicId);

private:
    void loadPlaylists(bool);
    int getSongCountForPlaylist(int playlistId);
    void clearLayout(QLayout *layout);


    void loadPublicPlaylists();
    void loadAllPlaylists();

    QVBoxLayout *m_playlist_layout;
    QPushButton *m_backButton;
    int m_userId;
};
/*
class Playlist : public QWidget
{
    Q_OBJECT

public:
    Playlist(const QString& img, int playlistId, int songCount, const QString &playlistName, QWidget *parent = nullptr);

signals:
    void playlistClicked(int playlistId);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QHBoxLayout *m_layout;
    QVBoxLayout *m_text_layout;
    QLabel *m_img_lbl;
    QLabel *m_title_lbl;
    QLabel *m_song_lbl;
    int m_playlistId;
};*/


class Playlist : public QWidget
{
    Q_OBJECT

public:
    explicit Playlist(const QString& img, int playlistId, int songCount, const QString &playlistName, const QString &iconPath = QString(), QWidget *parent = nullptr);

signals:
    void playlistClicked(int playlistId);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QHBoxLayout *m_layout;
    QVBoxLayout *m_text_layout;
    QLabel *m_img_lbl;
    QLabel *m_title_lbl;
    QLabel *m_song_lbl;
    QLabel *m_icon_lbl; // QLabel for the privacy icon, can be null
    int m_playlistId;
};

} // namespace components
} // namespace ui

#endif // PLAYLIST_H
