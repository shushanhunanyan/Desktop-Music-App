#include "album.h"

namespace ui
{
namespace components
{

Album::Album(const QPixmap& img, int count, const QString &name, QWidget *parent)
    : QWidget(parent)
    , m_layout(new QHBoxLayout(this))
    , m_album_image(img)
    , m_count_of_songs(new QLabel(QString::number(count) + " songs", this))
    , m_album_title(new QLabel(name, this))
    , m_img_label(new QLabel(this))
{
    m_img_label->setPixmap(m_album_image);
    m_img_label->setScaledContents(true);
    m_img_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_img_label->setFixedSize(90, 90);

    m_album_title->setStyleSheet("color: white;");
    m_count_of_songs->setStyleSheet("color: white;");

    QVBoxLayout *textlayout = new QVBoxLayout();
    textlayout->addWidget(m_album_title);
    textlayout->addWidget(m_count_of_songs);

    m_layout->addWidget(m_img_label);
    m_layout->addLayout(textlayout);

    setLayout(m_layout);
}

}
}
