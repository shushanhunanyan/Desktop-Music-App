#ifndef FOOTER_COMPONENTS_H
#define FOOTER_COMPONENTS_H


#include "src/core/Database/databasemanager.h"


#include <QObject>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QMediaPlayer>
#include <QLabel>
#include <QComboBox>
#include <QPixmap>
#include <QSqlDatabase>
#include <QProcess>
#include <QUrlQuery>
#include <QMediaMetaData>
#include <QtCore>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDir>
#include <QMessageBox>

namespace ui
{
namespace components
{

/*

class LeftSide : public QWidget {
    Q_OBJECT

public:
    explicit LeftSide(int id, QWidget *parent = nullptr);
    ~LeftSide();

private:
    void loadFriends(int userId);

    QComboBox *sendToFriendComboBox;
    QLabel *songName;
    QPushButton *playButton;
    int m_userId;
};*/


class LeftSide : public QWidget {
    Q_OBJECT

public:
    explicit LeftSide(int id, QWidget *parent = nullptr);
    ~LeftSide();

signals:
    void sendSongToFriend(int friendId, const QString &songName);

private slots:
    void onSendButtonClicked();

private:
    void loadFriends(int userId);

    QComboBox *sendToFriendComboBox;
    QLabel *songName;
    QPushButton *playButton;
    int m_userId;
};

} // namespace components
} // namespace ui

#endif // FOOTER_COMPONENTS_H
