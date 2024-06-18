// In user.cpp
#include "user.h"

#include <QPainterPath>
#include <QPainter>
#include <QPixmap>
#include <QBitmap>
#include <QFileDialog>
#include <QBuffer>

namespace ui {
namespace components {

class CircularImageLoader {
public:
    static QPixmap loadCircularImage(const QString &imagePath) {
        QPixmap pixmap(imagePath);
        return createCircularPixmap(pixmap);
    }

    static QPixmap createCircularPixmap(const QPixmap &pixmap) {
        if (pixmap.isNull()) {
            return QPixmap();
        }

        int size = qMin(pixmap.width(), pixmap.height());
        QPixmap squarePixmap = pixmap.copy((pixmap.width() - size) / 2, (pixmap.height() - size) / 2, size, size);

        QPixmap circularPixmap(size, size);
        circularPixmap.fill(Qt::transparent);

        QPainter painter(&circularPixmap);
        QPainterPath path;
        path.addEllipse(0, 0, size, size);
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, squarePixmap);

        return circularPixmap;
    }

    static QPixmap loadCircularImageFromData(const QByteArray &data) {
        QPixmap pixmap;
        pixmap.loadFromData(data);
        return createCircularPixmap(pixmap);
    }

    static QByteArray pixmapToByteArray(const QPixmap &pixmap) {
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::WriteOnly);
        pixmap.save(&buffer, "PNG");
        return byteArray;
    }
};


User::User(int userId, int guestId, QWidget *parent)
    : QWidget(parent)
    , m_usernameLabel(new ClickableLabel(this)) // Use ClickableLabel
    , m_profileLabel(new ClickableLabel(this)) // Use ClickableLabel
    , m_playlistLayout(new QVBoxLayout())
    , m_artistsLayout(new QVBoxLayout())
    , userId(userId)
    , guestId(guestId)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QHBoxLayout *usrlayout = new QHBoxLayout();
    usrlayout->addWidget(m_profileLabel);
    usrlayout->addWidget(m_usernameLabel);
    usrlayout->setAlignment(Qt::AlignLeft);
    usrlayout->setSpacing(20);

    layout->addLayout(usrlayout);
    layout->addLayout(m_playlistLayout);
    layout->addLayout(m_artistsLayout);

    setLayout(layout);

    loadUserData(userId);

    connect(m_profileLabel, &ClickableLabel::clicked, this, &User::changeProfilePicture);
    connect(m_usernameLabel, &ClickableLabel::clicked, this, &User::openUserCentralAreaViewModel); // Connect username click to slot
}

void User::loadUserData(int userId)
{
    QSqlDatabase db = DatabaseManager::instance()->database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Failed to connect to the database.");
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT username, profile_pic FROM users WHERE id = :userId");
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Error loading user data:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString username = query.value("username").toString();
        m_usernameLabel->setText(username);

        QByteArray profilePicData = query.value("profile_pic").toByteArray();
        QPixmap profilePixmap = CircularImageLoader::loadCircularImageFromData(profilePicData);
        if (profilePixmap.isNull()) {
            profilePixmap = CircularImageLoader::loadCircularImage(":resources/images/profile_pic.jpg");
        }
        m_profileLabel->setPixmap(profilePixmap.scaled(80, 80, Qt::KeepAspectRatio));
    }
}

void User::changeProfilePicture()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.jpeg *.bmp *.gif)"));
    if (!imagePath.isEmpty()) {
        QPixmap circularPixmap = CircularImageLoader::loadCircularImage(imagePath);
        if (!circularPixmap.isNull()) {
            m_profileLabel->setPixmap(circularPixmap.scaled(80, 80, Qt::KeepAspectRatio));
            saveProfilePictureToDatabase(imagePath);
            loadUserData(userId);
        } else {
            qDebug() << "Failed to load image:" << imagePath;
        }
    }
}

void User::saveProfilePictureToDatabase(const QString &imagePath)
{
    QSqlDatabase db = DatabaseManager::instance()->database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    QByteArray imageData;
    QFile file(imagePath);
    if (file.open(QIODevice::ReadOnly)) {
        imageData = file.readAll();
        file.close();
    } else {
        qDebug() << "Failed to open image file:" << imagePath;
        return;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE users SET profile_pic = :imageData WHERE id = :userId");
    query.bindValue(":imageData", imageData);
    query.bindValue(":userId", userId);
    if (!query.exec()) {
        qDebug() << "Error updating profile picture:" << query.lastError().text();
        return;
    }

    qDebug() << "Profile picture updated successfully!";
}

void User::openUserCentralAreaViewModel()
{
    ui::viewmodels::UserCentralAreaViewModel *userCentralArea = new ui::viewmodels::UserCentralAreaViewModel(userId, guestId);
    userCentralArea->show();
}


} // namespace components
} // namespace ui
