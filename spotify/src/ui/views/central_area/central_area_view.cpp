#include "src/ui/views/central_area/central_area_view.h"

#include "src/ui/components/user.h"
namespace ui
{
namespace views
{

CentralAreaView::CentralAreaView(int id, QWidget *parent)
    : QWidget{parent}
    , l1{new ui::components::MainList("Popular", this)}
    , l2{new ui::components::MainList("Shuffle", this)}
    , l3{new ui::components::MainList("Shuffle")}
    , m_layout{new QVBoxLayout(this)}
    , m_scrollArea(new QScrollArea(this))
{
    QWidget *containerWidget = new QWidget(this);
    QVBoxLayout *containerLayout = new QVBoxLayout(containerWidget);

    containerLayout->addWidget(l1);
    containerLayout->addWidget(l2);
    containerLayout->addWidget(l3);

    containerLayout->setAlignment(Qt::AlignTop);
    containerLayout->setContentsMargins(10, 10, 10, 10);

    containerWidget->setLayout(containerLayout);

    m_scrollArea->setWidget(containerWidget);
    m_scrollArea->setWidgetResizable(true);

    int widgetHeight = l1->sizeHint().height() + l2->sizeHint().height();
    m_scrollArea->setFixedHeight(widgetHeight);

    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QLabel *suggestedLabel = new QLabel("Suggested Songs");
    suggestedLabel->setStyleSheet("QLabel {"
                                      "    font-family: 'Arial';"    // Set the font family to Arial
                                  "    font-size: 24px;"        // Set the font size to make it larger
                                  "    font-weight: bold;"      // Make the font bold
                                  "    color: white;"           // Set the text color
                                  "    background-color: #121212;"  // Set a background color if needed
                                  "}");
    suggestedLabel->setAlignment(Qt::AlignTop);
    m_layout->addWidget(suggestedLabel);
    m_layout->setAlignment(Qt::AlignTop);
    m_layout->addWidget(m_scrollArea);

    setLayout(m_layout);

    m_scrollArea->setAttribute(Qt::WA_StyledBackground, true);
    m_scrollArea->setStyleSheet("QScrollArea {border: none; }");

    containerWidget->setStyleSheet("background-color: #121212;");
    this->setAttribute(Qt::WA_StyledBackground, true);

    connect(l1, &ui::components::MainList::listClicked, this, &CentralAreaView::handleSongSelection);
    connect(l2, &ui::components::MainList::listClicked, this, &CentralAreaView::handleSongSelection);
    connect(l3, &ui::components::MainList::listClicked, this, &CentralAreaView::handleSongSelection);

    setStyleSheet(
        "QScrollArea {"
        "    background-color: transparent;" // Set the background color of the scroll area
        "}"
        "QScrollBar:vertical {"
        "    border: none;"
        "    background: #121212;" // Set the background color of the scroll bar
        "    width: 12px;" // Set the width of the scroll bar
        "    margin: 0px 0px 0px 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #5a5a5a;" // Set the background color of the scroll bar handle
        "    min-height: 5px;" // Set the minimum height of the scroll bar handle
        "}"
        "QScrollBar::handle:vertical:hover {"
        "    background: #898989;" // Set the background color of the scroll bar handle when hovered
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "    background: transparent;" // Set the background color of the scroll bar arrows
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    background: transparent;" // Set the background color of the scroll bar page buttons
        "}"
        );

}

void CentralAreaView::handleSeeAll(bool isChecked, const QString& genre)
{
    if (genre == "Popular") {
        l1->setVisible(true);
        l2->setVisible(false);
        // l3->setVisible(false);
    } else if (genre == "Shuffle") {
        l1->setVisible(false);
        l2->setVisible(true);
        // l3->setVisible(false);
    }
}

void CentralAreaView::handleSongSelection(int id) {
    emit playMusic(id);
}



}
}
