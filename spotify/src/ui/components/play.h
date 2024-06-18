#ifndef PLAY_H
#define PLAY_H

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QMediaPlayer>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QByteArray>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QMouseEvent>

namespace ui {
namespace components {
/*
class Play : public QWidget
{
    Q_OBJECT

public:
    explicit Play(int music_id, QWidget *parent = nullptr);

public slots:
    void update(int music_id);
    void playButtonClicked(int music_id);
    void seekForward();
    void seekBackward();

private:
    QHBoxLayout *buttons;
    QPushButton *playButton;
    QPushButton *backwardButton;
    QPushButton *forwardButton;
    QPushButton *repeatButton;
    QPushButton *shuffleButton;
    QSlider *playSlide;
    QMediaPlayer *player;
    int m_music_id;

    QByteArray fetchAudioFileFromDatabase(int music_id);
    bool saveAudioDataToFile(const QByteArray &audioData, const QString &filePath);
    void updateSliderPosition(qint64 position);
    void updateSliderDuration(qint64 duration);
};*/

class Play : public QWidget
{
    Q_OBJECT

public:
    explicit Play(int music_id, QWidget *parent = nullptr);

public slots:
    void update(int music_id);
    void playButtonClicked(int music_id);
    void seekForward();
    void seekBackward();
    void seekPosition(int position);
    void sliderPressed();
    void sliderReleased();
    void playPrevious();
    void playNext();
    void toggleRepeatMode();

signals:
    void previousSong();
    void nextSong();

private:
    QHBoxLayout *buttons;
    QPushButton *playButton;
    QPushButton *backwardButton;
    QPushButton *forwardButton;
    QPushButton *repeatButton;
    QPushButton *shuffleButton;
    QSlider *playSlide;
    QMediaPlayer *player;
    int m_music_id;
    QList<int> history;  // History of played music IDs
    int historyIndex;    // Current index in the history

    QByteArray fetchAudioFileFromDatabase(int music_id);
    bool saveAudioDataToFile(const QByteArray &audioData, const QString &filePath);
    void updateSliderPosition(qint64 position);
    void updateSliderDuration(qint64 duration);
    bool eventFilter(QObject *object, QEvent *event);  // New method to handle slider click events
    enum RepeatMode { NoRepeat, RepeatAll, RepeatOne };
    RepeatMode repeatMode;
    bool replayNextTime;
};


} // namespace components
} // namespace ui

#endif // PLAY_H
