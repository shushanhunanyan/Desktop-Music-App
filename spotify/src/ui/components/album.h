#ifndef ALBUM_H
#define ALBUM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>

namespace ui
{
namespace components
{

class Album : public QWidget
{
public:
    explicit Album(const QPixmap&, int, const QString&, QWidget *parent = nullptr);

private:
    QHBoxLayout *m_layout;
    QPixmap m_album_image;
    QLabel *m_count_of_songs;
    QLabel *m_album_title;
    QLabel *m_img_label;
};

}
}
/*    QPixmap img(":/resources/Arno.jpeg");
    QLabel *imgLabel = new QLabel(this);
    imgLabel->setPixmap(img);
    imgLabel->setScaledContents(true);
    imgLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imgLabel->setFixedSize(90, 90);


    QVBoxLayout *textlayout = new QVBoxLayout();
    QLabel *title = new QLabel("Arno Bab.", this);
    QLabel *name = new QLabel("44 songs", this);
    title->setStyleSheet("color: white;");
    name->setStyleSheet("color: white;");

    textlayout->addWidget(title);
    textlayout->addWidget(name);

    QHBoxLayout *albom = new QHBoxLayout();
    albom->addWidget(imgLabel);
    albom->addLayout(textlayout);*/




#endif // ALBUM_H
