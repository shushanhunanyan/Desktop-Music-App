#ifndef RIGHTSIDEBARVIEW_H
#define RIGHTSIDEBARVIEW_H


#include "src/ui/components/user.h"
#include "src/ui/components/icon.h"
#include "src/ui/components/chatmanager.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QScrollArea>
#include <QSqlQuery>
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QDebug>
#include <QSqlError>

namespace ui
{
namespace views
{

/*
class Listening : public QWidget {
    Q_OBJECT

public:
    Listening(ui::components::User *user, QWidget *parent = nullptr);
    ~Listening();

signals:
    void chatRequested();

private slots:
    void openChat();

private:
    ui::components::User *m_user;
    QHBoxLayout *m_layout;
    ui::components::CreateIcon *m_msgicon;
};

class RightSidebarView : public QWidget {
    Q_OBJECT

public:
    RightSidebarView(int id, QWidget *parent = nullptr);
    ~RightSidebarView();

private slots:
    void filterUsers(const QString &searchText);
    void handleChatRequest(const QString &username);
    void showUserList();
    void showChatWidget();
    void onSendMessage(const QString &message);

private:
    void loadFriends();
    void loadUsers(const QString &filter);
    void applyScrollAreaStyles(QScrollArea *scroll_area);

    int m_userId;
    QLineEdit *m_search;
    QVBoxLayout *m_layout;
    QScrollArea *m_scrollArea;
    QList<Listening*> m_listeningWidgets;
    ChatWidget *m_chatWidget;
    QWidget *m_scrollWidget;
};

*/

class Listening : public QWidget {
    Q_OBJECT

public:
    Listening(ui::components::User *user, QWidget *parent = nullptr);
    ~Listening();
    void changeIcon(const QPixmap &pixma);
signals:
    void chatRequested();

private slots:
    void openChat();

private:
    ui::components::User *m_user;
    QVBoxLayout *m_layout;
    ui::components::CreateIcon *m_msgicon;
};

class RightSidebarView : public QWidget {
    Q_OBJECT

public:
    RightSidebarView(int id, QWidget *parent = nullptr);
    ~RightSidebarView();

private slots:
    void filterUsers(const QString &searchText);
    void handleChatRequest(const QString &username);
    void showUserList();
    void showChatWidget();
    void onSendMessage(const QString &message);

private:
    void loadFriends();
    void loadUsers(const QString &filter);
    void applyScrollAreaStyles(QScrollArea *scroll_area);

    int m_userId;
    QLineEdit *m_search;
    QVBoxLayout *m_layout;
    QScrollArea *m_scrollArea;
    QList<Listening*> m_listeningWidgets;
    ChatWidget *m_chatWidget;
    QWidget *m_scrollWidget;
};

} // namespace views
} // namespace ui

#endif // RIGHTSIDEBARVIEW_H
