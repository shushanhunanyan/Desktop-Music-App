#ifndef USERCENTRALAREAVIEWMODEL_H
#define USERCENTRALAREAVIEWMODEL_H

#include "src/ui/components/user.h"
#include "src/ui/views/central_area/central_area_view.h"

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>

namespace ui {
namespace components {
class User;
} // namespace components
}

namespace ui {
namespace viewmodels {


class UserCentralAreaViewModel : public QWidget
{
    Q_OBJECT
public:
    explicit UserCentralAreaViewModel(int user_id, int guest_id, QWidget *parent = nullptr);
    ~UserCentralAreaViewModel() = default;

private slots:
    void handleAddFriendButtonClick();
    int getFriendCount(int userId);
    int getFriendMeCount(int userId);

private:
    void applyScrollAreaStyles(QScrollArea *scroll_area);
    bool addFriendToDatabase(int userId, int friendId);
    bool removeFriendFromDatabase(int userId, int friendId);
    bool isFriend(int userId, int friendId);
    void updateAddFriendButton();

    int m_userId;
    int m_guestId;
    QVBoxLayout *m_layout;
    ui::components::User *m_user;
    QPushButton *m_addFriendButton; // Add friend button member
    bool m_isFriend; // Track if the current user is already a friend
};

}
}
#endif // USERCENTRALAREAVIEWMODEL_H
