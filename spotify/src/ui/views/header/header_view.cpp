#include "header_view.h"

#include "src/ui/views/login/welcome.h"


namespace ui
{
namespace views
{

//HeaderView::HeaderView(int id, QWidget *parent)
HeaderView::HeaderView(int id, ui::views::FooterView* footerView, QWidget *parent)
    : QWidget{parent}
    , m_search{new components::Search(footerView, this)}
    , m_layout{new QHBoxLayout()}
    , m_logoutButton{new QPushButton("Log Out")}
{
    m_layout->addWidget(m_search);

    QHBoxLayout *logoutLayout = new QHBoxLayout();
    logoutLayout->addWidget(m_logoutButton);
    logoutLayout->setAlignment(Qt::AlignTop);
    m_logoutButton->setStyleSheet(
        "QPushButton {"
        "    border: none;"
        "    background-color: #ffffff;"
        "    color: #060606;"
        "    margin: 3px;"
        "    padding: 12px 18px;"
        "    text-align: center;"
        "    text-transform: uppercase;"
        "    border-radius: 20px;"
        "    font-weight: bold;"  // Make the font bold
        "}"
        "QPushButton:hover {"
        "    margin-top: 2px;"
        "    margin-left: 2px;"
        "    margin-right: 2px;"
        "    background-position: right center;" // Change the direction of the background position on hover
        "    color: #060606;"
        "    text-decoration: none;"
        "}"
        );

    m_layout->addLayout(logoutLayout);

    this->setLayout(m_layout);
    this->setAttribute(Qt::WA_StyledBackground, true);

    connect(m_logoutButton, &QPushButton::clicked, this, &HeaderView::handleLogout);

}


void HeaderView::handleLogout()
{
    QWidget *mainWindow = this->parentWidget();
    if (mainWindow)
    {
        mainWindow->close();
    }
    else
    {
        qDebug() << "Unable to find parent main window";
    }

    Welcome *welcomePage = new Welcome;
    welcomePage->show();
}

} // namespace views
} // namespace ui
