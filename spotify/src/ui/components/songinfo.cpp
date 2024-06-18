#include "songinfo.h"
#include "clickablelabel.h"

namespace ui
{
namespace components
{

Song::Song(int musicId, QWidget *parent)
    : QWidget(parent)
    , m_textLayout(new QVBoxLayout())
    , m_layout(new QHBoxLayout(this))
    , m_titleLabel(new QLabel(this))
    , m_artistLabel(new QLabel(this))
    , m_imgLabel(new QLabel(this))
    , m_musicId(musicId)
{
    int imageSize = 90;
    m_imgLabel->setFixedSize(imageSize, imageSize);

    m_imgLabel->setScaledContents(true);
    m_imgLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    m_textLayout->addWidget(m_titleLabel);
    m_textLayout->addWidget(m_artistLabel);

    m_layout->addWidget(m_imgLabel);
    m_layout->addLayout(m_textLayout);

    setLayout(m_layout);

    loadSongData(musicId);
}



void Song::loadSongData(int musicId) {
    m_musicId = musicId;

    QSqlDatabase db = DatabaseManager::instance()->database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Failed to connect to the database.");
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT title, artist, image FROM music WHERE music_id = :musicId");
    query.bindValue(":musicId", musicId);

    if (!query.exec()) {
        qDebug() << "Error loading song data:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString title = query.value("title").toString();
        QString artist = query.value("artist").toString();
        QByteArray imageData = query.value("image").toByteArray();

        m_titleLabel->setText(title);
        m_artistLabel->setText(artist);

        QPixmap pixmap;
        if (!pixmap.loadFromData(imageData)) {
            pixmap.load(":/resources/images/def-music.png");
        }
        // Scale the pixmap to fit within the fixed size while keeping aspect ratio
        m_imgLabel->setPixmap(pixmap.scaled(m_imgLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        m_imgLabel->setStyleSheet("border: 2px solid #444; padding: 5px; background-color: #222;");
    }
}


void Song::update(int musicId)
{
    m_musicId = musicId;

    QSqlDatabase db = DatabaseManager::instance()->database();
    QSqlQuery query(db);
    query.prepare("SELECT title, artist, image FROM music WHERE music_id = :musicId");
    query.bindValue(":musicId", musicId);
    if (query.exec()) {
        if (query.next()) {
            QString title = query.value("title").toString();
            QString artist = query.value("artist").toString();
            QByteArray imageData = query.value("image").toByteArray();

            // Update the song's title and artist
            m_titleLabel->setText(title);
            m_artistLabel->setText(artist);

            QPixmap pixmap;
            if (!pixmap.loadFromData(imageData)) {
                pixmap.load(":/resources/images/def-music.png");
            }
            m_imgLabel->setPixmap(pixmap.scaled(m_imgLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            m_imgLabel->setStyleSheet("border: 2px solid #444; padding: 5px; background-color: #222;");
        } else {
            // Handle the case where the song with the provided id is not found
            qDebug() << "Song with id" << musicId << "not found in the database.";
        }
    } else {
        // Handle the case where the query execution fails
        qDebug() << "Failed to execute query to fetch song with id" << musicId;
    }

}

void Song::mousePressEvent(QMouseEvent *event)
{
    emit clicked(m_musicId); // Assuming songId is a member variable of Song
}

} // namespace components
} // namespace ui
