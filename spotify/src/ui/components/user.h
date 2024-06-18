// In user.h
#ifndef USER_H
#define USER_H

#include "src/core/Database/databasemanager.h"
#include "src/viewmodels/usercentralareaviewmodel.h"

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainterPath>
#include <QPainter>
#include <QPixmap>
#include <QBitmap>
#include <QFileDialog>

namespace ui {
namespace components {

class ClickableLabel : public QLabel {
    Q_OBJECT
public:
    explicit ClickableLabel(QWidget* parent = nullptr) : QLabel(parent) {}

signals:
    void clicked(); // Define a custom clicked signal

protected:
    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            emit clicked(); // Emit the custom clicked signal when left mouse button is pressed
        }
    }
};


class User : public QWidget {
    Q_OBJECT

public:
    User(int userId, int guestId, QWidget *parent = nullptr);

    int getUserId() { return userId; }
private slots:
    void changeProfilePicture();
    void loadUserData(int userId);
    void saveProfilePictureToDatabase(const QString &imagePath);
    void openUserCentralAreaViewModel();
 //   void handleUsernameClicked(int id);
signals:
    void usernameClicked(int id);

private:
    ClickableLabel *m_usernameLabel; // Use ClickableLabel instead of QLabel
    ClickableLabel *m_profileLabel;
    QVBoxLayout *m_playlistLayout;
    QVBoxLayout *m_artistsLayout;
    int userId;
    int guestId;
};

} // namespace components
} // namespace ui

#endif // USER_H
