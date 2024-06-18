#include "artist.h"

namespace ui {
namespace components {

Artist::Artist(int id, QWidget *parent)
    : QWidget(parent)
    , m_layout{new QHBoxLayout(this)}
    , m_img_lbl{new QLabel(this)}
    , m_artist_name_lbl{new QLabel(this)}
{
    int imageSize = 90;
    m_img_lbl->setFixedSize(imageSize, imageSize);

    m_img_lbl->setScaledContents(true);
    m_img_lbl->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    m_layout->addWidget(m_img_lbl);
    m_layout->addWidget(m_artist_name_lbl);

    setLayout(m_layout);

    loadArtistData(id);
}

void Artist::loadArtistData(int id) {
    QSqlDatabase db = DatabaseManager::instance()->database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Failed to connect to the database.");
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT artist, image FROM music WHERE music_id = :music_id");
    query.bindValue(":music_id", id);

    if (!query.exec()) {
        qDebug() << "Error loading artist data:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString artist = query.value("artist").toString();
        QByteArray imageData = query.value("image").toByteArray();

        m_artist_name_lbl->setText(artist);

        QPixmap pixmap;
        if (!pixmap.loadFromData(imageData)) {
            pixmap.load(":/resources/images/def-music.png");
        }
        // Scale the pixmap to fit within the fixed size while keeping aspect ratio
        m_img_lbl->setPixmap(pixmap.scaled(m_img_lbl->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        m_img_lbl->setStyleSheet("border: 2px solid #444; padding: 5px; background-color: #222;");
    }
}

} // namespace components
} // namespace ui
