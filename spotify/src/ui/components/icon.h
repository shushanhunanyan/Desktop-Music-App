#ifndef ICON_H
#define ICON_H

#include "src/core/Database/databasemanager.h"

#include <QPixmap>
#include <QString>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QLabel>
#include <QHBoxLayout>

namespace ui {
namespace components {

class CreateIcon : public QWidget
{
    Q_OBJECT
public:
    QPixmap m_iconPixmap;

    explicit CreateIcon(const QPixmap&, int, QWidget *parent = nullptr); // Remove default argument for size

    void setIconPixmap(const QPixmap &pixmap);
    void setIconSize(int size);
    void setIconStyle(const QString &style);
signals:
    void clicked();

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
private:
    int m_size;
    QString m_style;
};


class InfoLabel : public QWidget
{
public:
    InfoLabel(const QPixmap &icon, int labelValue, QWidget *parent = nullptr) : QWidget{parent} {
        m_icon = new CreateIcon(icon, 28); // Assuming CreateIcon has a copy constructor or appropriate constructor
        m_label = new QLabel(QString::number(labelValue));

        m_layout = new QHBoxLayout(this);
        m_layout->addWidget(m_icon);
        m_layout->addWidget(m_label);

    //setStyleSheet("QLabel { color: white; }");
    }
private:
    CreateIcon *m_icon;
    QLabel *m_label; // Change QLabel to QLabel*
    QHBoxLayout *m_layout;
};



/*    QHBoxLayout *m_layout = new QHBoxLayout();
    QLabel *m_musicLabel = new QLabel("0");
    QPixmap musicPixmap(":/resources/wh-music.png");
    QLabel *musicIconLabel = new QLabel();
    musicIconLabel->setPixmap(musicPixmap);
    musiclayout->addWidget(musicIconLabel);
    musiclayout->addWidget(musicLabel);*/

} // namespace components
} // namespace ui

#endif // ICON_H
