#include "play.h"
#include "src/ui/components/addtoplaylistdialog.h"
#include "src/core/Database/databasemanager.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDir>
#include <QDebug>

namespace ui
{
namespace components
{


Play::Play(int music_id, QWidget *parent)
    : QWidget(parent)
    , buttons(new QHBoxLayout)
    , playButton(new QPushButton(QIcon(":resources/wh-play.png"), ""))
    , backwardButton(new QPushButton(QIcon(":resources/wh-fast-backward.png"), ""))
    , forwardButton(new QPushButton(QIcon(":/resources/wh-fast-forward.png"), ""))
    , repeatButton(new QPushButton(QIcon(":/resources/wh-repeat.png"), ""))
    , shuffleButton(new QPushButton(QIcon(":/resources/wh-shuffle.png"), ""))
    , playSlide(new QSlider(Qt::Horizontal, this))
    , player(new QMediaPlayer(this))
    , m_music_id(music_id)
    , historyIndex(-1)  // Initialize history index
    , repeatMode(NoRepeat)
    , replayNextTime(false)
{
    QString buttonStyle = QString("background-color: transparent; border: none; "
                                  "icon-size: %1px;"
                                  "margin-left: 5px; margin-right: 5px;").arg(20);

    QString buttonStyle1 = QString("background-color: transparent; border: none; "
                                   "icon-size: %1px;"
                                   "margin-left: 5px; margin-right: 5px;").arg(40);

    playButton->setStyleSheet(buttonStyle1);
    backwardButton->setStyleSheet(buttonStyle);
    forwardButton->setStyleSheet(buttonStyle);
    repeatButton->setStyleSheet(buttonStyle);
    shuffleButton->setStyleSheet(buttonStyle);

    buttons->addWidget(shuffleButton);
    buttons->addWidget(backwardButton);
    buttons->addWidget(playButton);
    buttons->addWidget(forwardButton);
    buttons->addWidget(repeatButton);

    buttons->setAlignment(Qt::AlignCenter);

    QVBoxLayout *platLayout = new QVBoxLayout();
    platLayout->addLayout(buttons);
    platLayout->addWidget(playSlide);

    QString handleStyle = QString("QSlider::handle:horizontal {"
                                  "    background-color: none;"
                                  "}");

    QString trackStyle = QString("QSlider::groove:horizontal {"
                                 "    background-color: white;"
                                 "    height: 5px; "
                                 "    margin: 0px; "
                                 "    border-radius: 3px;"
                                 "}");

    QString playedStyle = QString("QSlider::add-page:horizontal {"
                                  "    background-color: #808080;"
                                  "}");

    QString remainingStyle = QString("QSlider::sub-page:horizontal {"
                                     "    background-color: white;"
                                     "}");

    playSlide->setStyleSheet(handleStyle + playedStyle + remainingStyle + trackStyle);

    setLayout(platLayout);

    connect(backwardButton, &QPushButton::clicked, this, &Play::seekBackward);
    connect(forwardButton, &QPushButton::clicked, this, &Play::seekForward);
    connect(playButton, &QPushButton::clicked, [this]() { playButtonClicked(m_music_id); });
    connect(player, &QMediaPlayer::positionChanged, this, &Play::updateSliderPosition);
    connect(player, &QMediaPlayer::durationChanged, this, &Play::updateSliderDuration);
    connect(shuffleButton, &QPushButton::clicked, this, [this]() {
        AddToPlaylistDialog dialog(1, m_music_id, this);
        dialog.exec();
    });

    connect(playSlide, &QSlider::sliderMoved, this, &Play::seekPosition);
    connect(playSlide, &QSlider::sliderPressed, this, &Play::sliderPressed);
    connect(playSlide, &QSlider::sliderReleased, this, &Play::sliderReleased);
    connect(repeatButton, &QPushButton::clicked, this, &Play::toggleRepeatMode);

    playSlide->installEventFilter(this);  // Install the event filter

    // Initialize the history with the first song
}

bool Play::eventFilter(QObject *object, QEvent *event) {
    if (object == playSlide && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        int duration = playSlide->maximum();
        int position = (mouseEvent->pos().x() * duration) / playSlide->width();
        playSlide->setValue(position);
        seekPosition(position);
        return true;
    }
    return QWidget::eventFilter(object, event);
}

void Play::playButtonClicked(int music_id) {
    m_music_id = music_id;

    if (player->state() == QMediaPlayer::PlayingState) {
        player->pause();
        playButton->setIcon(QIcon(":/resources/wh-play.png"));
    } else {
        if (player->state() == QMediaPlayer::StoppedState) {
            QByteArray audioData = fetchAudioFileFromDatabase(music_id);
            if (audioData.isEmpty()) {
                QMessageBox::warning(this, "Error", "Failed to retrieve audio file from the database.");
                return;
            }

            QString tempFilePath = QDir::tempPath() + "/temp_audio_file.mp3";
            if (!saveAudioDataToFile(audioData, tempFilePath)) {
                QMessageBox::warning(this, "Error", "Failed to save audio file.");
                return;
            }

            player->setMedia(QUrl::fromLocalFile(tempFilePath));
        }
        player->play();
        playButton->setIcon(QIcon(":/resources/wh-pause.png"));
        // Update the history
        if (history.isEmpty() || history.last() != music_id) {
            history.append(music_id);
            historyIndex = history.size() - 1;
        }
    }
}

void Play::updateSliderPosition(qint64 position) {
    playSlide->setValue(position);
}

void Play::updateSliderDuration(qint64 duration) {
    playSlide->setMaximum(duration);
}

void Play::sliderPressed() {
    if (player->state() == QMediaPlayer::PlayingState) {
        player->pause();
    }
}

void Play::sliderReleased() {
    player->setPosition(playSlide->value());
    if (player->state() != QMediaPlayer::PlayingState) {
        player->play();
    }
}

void Play::seekPosition(int position) {
    player->setPosition(position);
}

void Play::update(int music_id) {
    m_music_id = music_id;

    if (player->state() == QMediaPlayer::PlayingState || player->state() == QMediaPlayer::PausedState) {
        player->stop();
    }

    QByteArray audioData = fetchAudioFileFromDatabase(music_id);
    if (audioData.isEmpty()) {
        QMessageBox::warning(this, "Error", "Failed to retrieve audio file from the database.");
        return;
    }

    QString tempFilePath = QDir::tempPath() + "/temp_audio_file.mp3";
    if (!saveAudioDataToFile(audioData, tempFilePath)) {
        QMessageBox::warning(this, "Error", "Failed to save audio file.");
        return;
    }

    player->setMedia(QUrl::fromLocalFile(tempFilePath));
    player->play();
    playButton->setIcon(QIcon(":/resources/wh-pause.png"));
    // Update the history
    if (history.isEmpty() || history.last() != music_id) {
        history.append(music_id);
        historyIndex = history.size() - 1;
    }
}

void Play::seekBackward() {
    playPrevious();
}

void Play::seekForward() {
    playNext();
}

QByteArray Play::fetchAudioFileFromDatabase(int music_id) {
    m_music_id = music_id;
    QSqlDatabase db = DatabaseManager::instance()->database();
    if (!db.isOpen()) {
        QMessageBox::warning(this, "Error", "Failed to connect to the database.");
        qDebug() << "Failed to connect to the database.";
        return QByteArray();
    }

    QSqlQuery query(db);
    query.prepare("SELECT music FROM music WHERE music_id = :music_id");
    query.bindValue(":music_id", music_id);

    if (!query.exec()) {
        QMessageBox::warning(this, "Error", "Failed to retrieve audio file from the database.");
        qDebug() << "Database error:" << query.lastError().text();
        return QByteArray();
    }

    QByteArray audioData;
    if (query.next()) {
        audioData = query.value(0).toByteArray();
    } else {
        QMessageBox::warning(this, "Error", "No audio file found for the given music ID.");
        qDebug() << "No audio file found for the given music ID.";
    }

    return audioData;
}

bool Play::saveAudioDataToFile(const QByteArray &audioData, const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(audioData);
    file.close();
    return true;
}


void Play::playPrevious() {
    if (historyIndex > 0) {
        --historyIndex;
        int previousMusicId = history[historyIndex];
        update(previousMusicId);
    }
}

void Play::playNext() {
    if (historyIndex < history.size() - 1) {
        ++historyIndex;
        int nextMusicId = history[historyIndex];
        update(nextMusicId);
    } else {
        update(++m_music_id);
    }
}


void Play::toggleRepeatMode()
{
    switch (repeatMode) {
    case RepeatAll:
        repeatMode = RepeatOne;
        repeatButton->setIcon(QIcon(":/resources/gr-repeat.png"));
        replayNextTime = true;  // Set flag to replay next time
        break;
    case RepeatOne:
        repeatMode = NoRepeat;
        repeatButton->setIcon(QIcon(":/resources/wh-repeat.png"));
        replayNextTime = false;  // No need to replay next time
        break;
    }
}


}
}
