#include "footer_view.h"
#include "src/ui/components/header_components.h"

namespace ui
{
namespace views
{


FooterView::FooterView(int id, QWidget *parent)
    : QWidget{parent}
    , m_layout{new QHBoxLayout}
    , m_song{new components::Song(0, this)}
    , m_play{new components::Play(0, this)}
    , m_sendToFriend{new components::LeftSide(id, this)}
{
    m_layout->addWidget(m_song);
    m_layout->addWidget(m_play);
    m_layout->addWidget(m_sendToFriend);

    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setStyleSheet("FooterView {border: 2px solid black;}");
    this->setLayout(m_layout);

    connect(this, &FooterView::playMusic, m_play, &ui::components::Play::update);
    connect(this, &FooterView::playMusic, m_play, &ui::components::Play::playButtonClicked);
    connect(this, &FooterView::playMusic, m_song, &ui::components::Song::update);

 //   connect(this, &FooterView::playMusic, m_song, &ui::components::Song::update);
}

void FooterView::onUpdateFooter(int musicId) {
    emit playMusic(musicId);
}

void FooterView::handleSongSelection(int id) {
    m_song->update(id);
    m_play->update(id); // Ensure this calls the update method}
}


} // namespace views
} // namespace ui

