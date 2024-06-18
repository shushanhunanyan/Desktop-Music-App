#ifndef FOOTERVIEW_H
#define FOOTERVIEW_H

#include "src/ui/components/footer_components.h"
#include "src/ui/components/songinfo.h"
#include "src/ui/components/play.h"
#include "src/ui/components/songlist.h"


#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>

namespace ui
{
namespace views
{

class FooterView : public QWidget
{
    Q_OBJECT

public:
    explicit FooterView(int id, QWidget *parent = nullptr);
    void update(int id);

signals:
    void playMusic(int musicId);
    void setSong(int musicId);

public slots:
    void onUpdateFooter(int musicId);
    void handleSongSelection(int id);

private:
    QHBoxLayout *m_layout;
    components::Song *m_song;
    components::Play *m_play;
    components::LeftSide *m_sendToFriend;
};


} // namespace views
} // namespace ui

#endif // FOOTERVIEW_H
