#ifndef LEFTSIDEBARVIEW_H
#define LEFTSIDEBARVIEW_H

#include "src/core/Database/databasemanager.h"
#include "src/ui/components/user.h"
#include "src/ui/components/playlist.h"
#include "src/ui/components/artist.h"
#include "src/ui/components/icon.h"


#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QTabWidget>
#include <QPushButton>

namespace ui
{
namespace views
{

class LeftSidebarView : public QWidget
{
    Q_OBJECT

public:
    explicit LeftSidebarView(int userId, QWidget *parent = nullptr);
    void setupPlaylistsTab(int userId);
    void setupArtistsTab(int userId);
    void setupSongsTab(int userId);
    void applyScrollAreaStyles(QScrollArea *scroll_area);
    void loadUserPlaylistSongs(int userId, int playlistId);

signals:
    void songClicked(int musicId);
    void songSelected(int musicId);

private slots:
    void addNewPlaylist(const QString &img, int playlistId, const QString &playlistName, bool);
    int getFriendCount(int);
    void handleSongClicked(int);
private:
    QVBoxLayout *m_layout;
    ui::components::User *m_user;
    QTabWidget *m_tabWidget;
    QVBoxLayout *m_playlist_layout;
    int m_userId;
};

} // namespace views
} // namespace ui




#endif // LEFTSIDEBARVIEW_H
