#include "right_sidebar_view.h"


namespace ui
{
namespace views
{
/*
Listening::Listening(ui::components::User *user, QWidget *parent)
    : QWidget(parent),
    m_user(user),
    m_layout(new QHBoxLayout(this)),
    m_msgicon(nullptr)
{
    QPixmap messagePixmap(":/resources/wh-message.png");
    m_msgicon = new ui::components::CreateIcon(messagePixmap, 25);

    m_layout->addWidget(user);
    m_layout->addWidget(m_msgicon);

    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setLayout(m_layout);

    connect(m_msgicon, &ui::components::CreateIcon::clicked, this, &Listening::openChat);
}

void Listening::openChat() {
    emit chatRequested();
}

Listening::~Listening() {
    delete m_user;
}

RightSidebarView::RightSidebarView(int id, QWidget *parent)
    : QWidget{parent},
    m_userId{id},
    m_search{new QLineEdit(this)},
    m_layout{new QVBoxLayout()},
    m_scrollArea{new QScrollArea(this)},
    m_chatWidget{new ChatWidget(this)},
    m_scrollWidget{new QWidget()}
{
    setMinimumSize(330, 400);

    m_search->setPlaceholderText("Find User");
    m_layout->addWidget(m_search);

    m_scrollArea->setWidgetResizable(true);
    applyScrollAreaStyles(m_scrollArea);

    m_scrollArea->setWidget(m_scrollWidget);
    m_scrollWidget->setStyleSheet("background-color: #212121;");
    QVBoxLayout *scrollLayout = new QVBoxLayout(m_scrollWidget);
    m_scrollWidget->setLayout(scrollLayout);

    m_layout->addWidget(m_scrollArea);
    m_layout->addWidget(m_chatWidget);
    m_chatWidget->hide();

    m_layout->setStretch(0, 1);
    m_layout->setStretch(1, 1);
    this->setStyleSheet("QLabel { font-size: 14px; color: white; }");

    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setLayout(m_layout);

    connect(m_search, &QLineEdit::textChanged, this, &RightSidebarView::filterUsers);
    connect(m_chatWidget, &ChatWidget::backButtonClicked, this, &RightSidebarView::showUserList);
    connect(m_chatWidget, &ChatWidget::sendMessage, this, &RightSidebarView::onSendMessage);

    loadFriends();
}

void RightSidebarView::applyScrollAreaStyles(QScrollArea *scroll_area) {
    scroll_area->setStyleSheet(
        "QScrollArea {"
        "    background-color: transparent;"
        "}"
        "QScrollBar:vertical {"
        "    border: none;"
        "    background: #121212;"
        "    width: 1px;"
        "    margin: 0px 0px 0px 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #5a5a5a;"
        "    min-height: 2px;"
        "    max-height: 5px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "    background: #898989;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    background: transparent;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    background: transparent;"
        "}"
        );
}

RightSidebarView::~RightSidebarView() {
    qDeleteAll(m_listeningWidgets);
}

void RightSidebarView::filterUsers(const QString &searchText) {
    qDeleteAll(m_listeningWidgets);
    m_listeningWidgets.clear();

    if (searchText.isEmpty()) {
        loadFriends();
    } else {
        loadUsers(searchText);
    }
}

void RightSidebarView::loadFriends() {
    QSqlQuery query;
    query.prepare("SELECT u.id, u.username FROM users u "
                  "JOIN friends f ON u.id = f.friend_id WHERE f.user_id = :userId");
    query.bindValue(":userId", m_userId);

    if (!query.exec()) {
        qDebug() << "Failed to query friends:" << query.lastError();
        return;
    }

    while (query.next()) {
        int friendId = query.value(0).toInt();
        QString username = query.value(1).toString();

        ui::components::User *user = new ui::components::User(friendId, m_userId, this);
        Listening *listening = new Listening(user, this);

        connect(listening, &Listening::chatRequested, [=]() { handleChatRequest(username); });

        static_cast<QVBoxLayout*>(m_scrollArea->widget()->layout())->addWidget(listening);
        m_listeningWidgets.append(listening);
    }
}

void RightSidebarView::loadUsers(const QString &filter) {
    QSqlQuery query;
    query.prepare("SELECT id, username FROM users WHERE username LIKE :filter");
    query.bindValue(":filter", "%" + filter + "%");

    if (!query.exec()) {
        qDebug() << "Failed to query users:" << query.lastError();
        return;
    }

    while (query.next()) {
        int userId = query.value(0).toInt();
        QString username = query.value(1).toString();

        ui::components::User *user = new ui::components::User(userId, m_userId, this);
        Listening *listening = new Listening(user, this);

        connect(listening, &Listening::chatRequested, [=]() { handleChatRequest(username); });

        static_cast<QVBoxLayout*>(m_scrollArea->widget()->layout())->addWidget(listening);
        m_listeningWidgets.append(listening);
    }
}

void RightSidebarView::handleChatRequest(const QString &username) {
    m_chatWidget->setUsername(username);
    showChatWidget();
}

void RightSidebarView::showUserList() {
    m_scrollArea->show();
    m_chatWidget->hide();
}

void RightSidebarView::showChatWidget() {
    m_scrollArea->hide();
    m_chatWidget->show();
}

void RightSidebarView::onSendMessage(const QString &message) {
    // Handle sending message (e.g., save to database, update chat history)
    qDebug() << "Send message:" << message;
    m_chatWidget->appendMessage("You: " + message);
}*/

using namespace ui::views;

Listening::Listening(ui::components::User *user, QWidget *parent)
    : QWidget(parent)
    , m_user(user)
    , m_layout(new QVBoxLayout(this))
    , m_msgicon(nullptr)
{
    QPixmap messagePixmap(":/resources/wh-message.png");
    m_msgicon = new ui::components::CreateIcon(messagePixmap, 25);

    QHBoxLayout *layout = new QHBoxLayout();

    QLabel *songlisten = new QLabel("Do I Wanna Know - Arctic Monkeys");

    if (user->getUserId() == 2) {
            songlisten->setText("Bellyache - Billie Eilish");
    } else if (user->getUserId() == 3) {
            songlisten->setText("Die For You - The Weeknd");
    } else if (user->getUserId() == 4) {
            songlisten->setText("Lose Yourself - Eminem");
    } else if (user->getUserId() == 6) {
    songlisten->setText("Elegy - Arno Babadzhanyan");
}
    layout->addWidget(user);
    layout->addWidget(m_msgicon);

    m_layout->addLayout(layout);
    m_layout->addWidget(songlisten);

    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setLayout(m_layout);

    connect(m_msgicon, &ui::components::CreateIcon::clicked, this, &Listening::openChat);
}

Listening::~Listening() {
    delete m_user;
}

void Listening::changeIcon(const QPixmap &pixmap) {
    m_msgicon->setIconPixmap(pixmap);
}

void Listening::openChat() {
    emit chatRequested();
}

RightSidebarView::RightSidebarView(int id, QWidget *parent)
    : QWidget{parent}
    , m_userId{id}
    , m_search{new QLineEdit(this)}
    , m_layout{new QVBoxLayout()}
    , m_scrollArea{new QScrollArea(this)}
    , m_chatWidget{new ChatWidget(this)}
    , m_scrollWidget{new QWidget()}
{
    setMinimumSize(330, 400);

    m_search->setPlaceholderText("Find User");
    m_layout->addWidget(m_search);

    m_scrollArea->setWidgetResizable(true);
    applyScrollAreaStyles(m_scrollArea);

    m_scrollArea->setWidget(m_scrollWidget);
    m_scrollWidget->setStyleSheet("background-color: #212121;");
    QVBoxLayout *scrollLayout = new QVBoxLayout(m_scrollWidget);
    m_scrollWidget->setLayout(scrollLayout);

    m_layout->addWidget(m_scrollArea);
    m_layout->addWidget(m_chatWidget);
    m_chatWidget->hide();

    m_layout->setStretch(0, 1);
    m_layout->setStretch(1, 1);
    this->setStyleSheet("QLabel { font-size: 14px; color: white; }");

    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setLayout(m_layout);

    connect(m_search, &QLineEdit::textChanged, this, &RightSidebarView::filterUsers);
    connect(m_chatWidget, &ChatWidget::backButtonClicked, this, &RightSidebarView::showUserList);
    connect(m_chatWidget, &ChatWidget::sendMessage, this, &RightSidebarView::onSendMessage);

    loadFriends();
}

void RightSidebarView::applyScrollAreaStyles(QScrollArea *scroll_area) {
    scroll_area->setStyleSheet(
        "QScrollArea {"
        "    background-color: transparent;"
        "}"
        "QScrollBar:vertical {"
        "    border: none;"
        "    background: #121212;"
        "    width: 1px;"
        "    margin: 0px 0px 0px 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #5a5a5a;"
        "    min-height: 2px;"
        "    max-height: 5px;"
        "}"
        "QScrollBar::handle:vertical:hover {"
        "    background: #898989;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    background: transparent;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    background: transparent;"
        "}"
        );
}

RightSidebarView::~RightSidebarView() {
    qDeleteAll(m_listeningWidgets);
}

void RightSidebarView::filterUsers(const QString &searchText) {
    qDeleteAll(m_listeningWidgets);
    m_listeningWidgets.clear();

    if (searchText.isEmpty()) {
        loadFriends();
    } else {
        loadUsers(searchText);
    }
}

void RightSidebarView::loadFriends() {
    QSqlQuery query;
    query.prepare("SELECT u.id, u.username FROM users u "
                  "JOIN friends f ON u.id = f.friend_id WHERE f.user_id = :userId");
    query.bindValue(":userId", m_userId);

    if (!query.exec()) {
        qDebug() << "Failed to query friends:" << query.lastError();
        return;
    }

    while (query.next()) {
        int friendId = query.value(0).toInt();
        QString username = query.value(1).toString();

        ui::components::User *user = new ui::components::User(friendId, m_userId, this);
        Listening *listening = new Listening(user, this);

        connect(listening, &Listening::chatRequested, [=]() { handleChatRequest(username); });

        static_cast<QVBoxLayout*>(m_scrollArea->widget()->layout())->addWidget(listening);
        m_listeningWidgets.append(listening);
    }
}

void RightSidebarView::loadUsers(const QString &filter) {
    QSqlQuery query;
    query.prepare("SELECT id, username FROM users WHERE username LIKE :filter");
    query.bindValue(":filter", "%" + filter + "%");

    if (!query.exec()) {
        qDebug() << "Failed to query users:" << query.lastError();
        return;
    }

    while (query.next()) {
        int userId = query.value(0).toInt();
        QString username = query.value(1).toString();

        ui::components::User *user = new ui::components::User(userId, m_userId, this);
        Listening *listening = new Listening(user, this);

        connect(listening, &Listening::chatRequested, [=]() { handleChatRequest(username); });

        static_cast<QVBoxLayout*>(m_scrollArea->widget()->layout())->addWidget(listening);
        m_listeningWidgets.append(listening);
    }
}

void RightSidebarView::handleChatRequest(const QString &username) {
    m_chatWidget->setUsername(username);
    showChatWidget();
}

void RightSidebarView::showUserList() {
    m_scrollArea->show();
    m_chatWidget->hide();
}

void RightSidebarView::showChatWidget() {
    m_scrollArea->hide();
    m_chatWidget->show();
}
/*////novu on prev
void RightSidebarView::onSendMessage(const QString &message) {
    // Handle sending message (e.g., save to database, update chat history)
    qDebug() << "Send message:" << message;
    m_chatWidget->appendMessage("You: " + message, true);
}
*/

void RightSidebarView::onSendMessage(const QString &message) {
    // Handle sending message (e.g., save to database, update chat history)
    qDebug() << "Send message:" << message;
    m_chatWidget->appendMessage("You: " + message, true);
    // Change icon color when a message is sent
    QPixmap messagePixmap(":/resources/green-message.png");
    for (auto listeningWidget : m_listeningWidgets) {
        listeningWidget->changeIcon(messagePixmap);
    }
}


} // namespace views
} // namespace ui
