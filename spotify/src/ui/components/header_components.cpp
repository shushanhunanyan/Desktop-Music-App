#include "header_components.h"
#include "src/core/Database/databasemanager.h"
#include "src/ui/views/footer/footer_view.h"

namespace ui {
namespace components {

Search::Search(QWidget *parent)
    : QWidget(parent)
    , searchInput(new QLineEdit(this))
    , resultList(new QListWidget(this))
    , resultContainer(new QWidget(this))
    , m_footerView(nullptr)
{

    constract();
}

Search::Search(ui::views::FooterView* footerView, QWidget *parent)
    : QWidget(parent)
    , searchInput(new QLineEdit(this))
    , resultList(new QListWidget(this))
    , resultContainer(new QWidget(this))
    , m_footerView(footerView)
{

    constract();
}

void Search::constract()
{    searchInput->setPlaceholderText("Search?");
    searchInput->setStyleSheet("QLineEdit { border-color: transparent; padding-left: 2px; }");

    QPixmap searchIcon(":resources/wh-search.png");
    QLabel *searchIconLabel = new QLabel();
    searchIconLabel->setPixmap(searchIcon.scaled(25, 25));

    QHBoxLayout *searchLayout = new QHBoxLayout();
    searchLayout->addWidget(searchIconLabel);
    searchLayout->addWidget(searchInput);

    resultContainer->setVisible(false); // Initially hide the results container

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(resultContainer);

    QVBoxLayout *resultLayout = new QVBoxLayout(resultContainer);
    resultLayout->addWidget(resultList);

    setLayout(mainLayout);
    setAttribute(Qt::WA_StyledBackground, true);

    connect(searchInput, &QLineEdit::returnPressed, this, &Search::performSearch);
    connect(resultList, &QListWidget::itemClicked, this, &Search::handleResultItemClick);

    if (!initializeDatabase()) {
        QMessageBox::critical(this, "Database Error", "Failed to connect to the database.");
    }

    // Apply style sheet
    setStyleSheet(
        "QScrollArea {"
        "    background-color: transparent;" // Set the background color of the scroll area
        "}"
        "QScrollBar:vertical {"
        "    border: none;"
        "    background: transparent;" // Set the background color of the scroll bar
        "    width: 10px;" // Set the width of the scroll bar
        "    margin: 0px 0px 0px 0px;"
        "}"
        "QScrollBar::handle:vertical {"
        "    background: #5a5a5a;" // Set the background color of the scroll bar handle
        "    min-height: 20px;" // Set the minimum height of the scroll bar handle
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
        "QWidget { background-color: #121212; }" // Background color for the widget
                  "QLineEdit { border: 1px solid white; border-radius: 5px; background-color: transparent; }" // Style for the search input
                  "QListWidget { border: none; background-color: transparent; }" // Style for the result list
                  "QListWidget::item { padding: 10px; border-bottom: 1px solid #555; background-color: transparent; color: white; }" // Style for each item
                  "QListWidget::item:selected { background-color: #242424; color: #e8e7e6; border: none; }" // Style for selected item
                  "QListWidget::item:hover { background-color: #242424;  border: none;}" // Style for hovered item
                  );
    connect(searchInput, &QLineEdit::returnPressed, this, &Search::performSearch);
    connect(resultList, &QListWidget::itemClicked, this, &Search::handleResultItemClick);

    if (!initializeDatabase()) {
        QMessageBox::critical(this, "Database Error", "Failed to connect to the database.");
    }

}


void Search::handleResultItemClick(QListWidgetItem* item)
{
    QString title;
    QString artist;

    QStringList parts = item->text().split(" - ");
    if (parts.size() >= 2) {
        title = parts[1].trimmed();  // Correct order: Title should be second part
        artist = parts[0].trimmed(); // Correct order: Artist should be first part
    }
    searchInput->setText(artist + " - " + title);

    qDebug() << "Searching for title:" << title << "and artist:" << artist;

    QSqlDatabase db = DatabaseManager::instance()->database();

    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Failed to connect to the database.");
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT music_id FROM music WHERE title = :title AND artist = :artist COLLATE NOCASE");
    query.bindValue(":title", title);
    query.bindValue(":artist", artist);

    if (!query.exec()) {
        QMessageBox::warning(this, "Search Error", "Failed to execute search query.");
        qDebug() << "Search error:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        int musicId = query.value("music_id").toInt();
        qDebug() << "Found music with ID:" << musicId;
        m_footerView->onUpdateFooter(musicId);
    } else {
        qDebug() << "No matching music found for title:" << title << "and artist:" << artist;
        m_footerView->onUpdateFooter(0);
    }

    resultContainer->setVisible(true);
}



bool Search::initializeDatabase()
{
    QSqlDatabase db = DatabaseManager::instance()->database();

    if (!db.open()) {
        qDebug() << "Database error:" << db.lastError().text();
        return false;
    }
    return true;
}

void Search::performSearch()
{
    QSqlDatabase db = DatabaseManager::instance()->database();
    resultList->clear();
    QString queryText = searchInput->text();

    if (queryText.isEmpty()) {
        resultContainer->setVisible(false);
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT title, artist FROM music WHERE title LIKE :search OR artist LIKE :search OR genre LIKE :search");
    query.bindValue(":search", "%" + queryText + "%");

    if (!query.exec()) {
        QMessageBox::warning(this, "Search Error", "Failed to execute search query.");
        qDebug() << "Search error:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QString result = query.value("artist").toString() + " - " + query.value("title").toString();
        resultList->addItem(result);
    }

    resultContainer->setVisible(true);
}


} // namespace components
} // namespace ui
