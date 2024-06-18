#include "adminwindow.h"
#include "src/ui/views/login/welcome.h"

/*
AdminWindow::AdminWindow(QWidget *parent)
    : QWidget(parent)
    , m_defaultImage(":/resources/images/def-music.png")
    , m_layout(new QHBoxLayout(this))
    , m_audioDropLabel(new QLabel("Drop audio files here", this))
    , m_imageDropLabel(new QLabel("Drop image files here", this))
    , m_titleEdit(new QLineEdit(this))
    , m_artistEdit(new QLineEdit(this))
    , m_albumEdit(new QLineEdit(this))
    , m_fileNameEdit(new QLineEdit(this))
    , m_titleleft(new QLabel("Add to Database", this))
    , m_titleright(new QLabel("Remove from Database", this))
    , m_genreEdit(new QLineEdit(this))
    , m_addToDB(new QPushButton("Add", this))
    , m_audioStatusLabel(new QLabel(this))
    , m_searchResultsLabel(new QLabel(this))
    , m_deleteButton(new QPushButton("Delete", this))
    , m_search(new ui::components::Search())
    , m_logout(new QPushButton("Log Out"))
{
    resize(1000, 500);
    setAcceptDrops(true);

    m_audioDropLabel->setFixedSize(200, 200);
    m_imageDropLabel->setFixedSize(200, 200);

    m_audioDropLabel->setAlignment(Qt::AlignCenter);
    m_audioDropLabel->setStyleSheet("QLabel { border: 2px dashed gray; color: white; }");
    m_imageDropLabel->setAlignment(Qt::AlignCenter);
    m_imageDropLabel->setStyleSheet("QLabel { border: 2px dashed gray; color: white; }");

    m_imageLabel = new QLabel(this);
    m_imageLabel->setPixmap(m_defaultImage);
    m_imageLabel->setFixedSize(100, 100);
    m_imageLabel->setScaledContents(true);

    m_audioStatusLabel->setAlignment(Qt::AlignCenter);
    m_searchResultsLabel->setAlignment(Qt::AlignCenter);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Title:", m_titleEdit);
    formLayout->addRow("Artist:", m_artistEdit);
    formLayout->addRow("Album:", m_albumEdit);
    formLayout->addRow("File Name:", m_fileNameEdit);
    formLayout->addRow("Genre:", m_genreEdit);
    formLayout->setVerticalSpacing(10);
    formLayout->setContentsMargins(10, 20, 10, 20);

    QString lineEditStyle = "QLineEdit { border: 1px solid rgba(255, 255, 255, 0.5); border-radius: 5px; color: white; }";
    m_titleEdit->setStyleSheet(lineEditStyle);
    m_artistEdit->setStyleSheet(lineEditStyle);
    m_albumEdit->setStyleSheet(lineEditStyle);
    m_fileNameEdit->setStyleSheet(lineEditStyle);
    m_genreEdit->setStyleSheet(lineEditStyle);

    QVBoxLayout *leftside = new QVBoxLayout;
    m_titleleft->setAlignment(Qt::AlignLeft);
    m_titleleft->setStyleSheet("font-size: 24px; font-weight: bold; color: white; margin-bottom: 20px;");
    leftside->addWidget(m_titleleft);
    leftside->addLayout(formLayout);
    leftside->addWidget(m_imageLabel);

    QHBoxLayout *dropLayout = new QHBoxLayout;
    dropLayout->addWidget(m_audioDropLabel);
    dropLayout->addWidget(m_imageDropLabel);
    leftside->addLayout(dropLayout);

    leftside->addWidget(m_audioStatusLabel);
    leftside->addWidget(m_addToDB);
    m_layout->addLayout(leftside);

    QFrame *line = new QFrame;
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);

    QHBoxLayout *lineLayout = new QHBoxLayout;
    lineLayout->addSpacing(20);
    lineLayout->addWidget(line);
    lineLayout->addSpacing(20);
    m_layout->addLayout(lineLayout);

    // Right side layout
    QVBoxLayout *rightSideLayout = new QVBoxLayout;

    QHBoxLayout *headerLayout = new QHBoxLayout;
    headerLayout->addWidget(m_titleright);
    headerLayout->addSpacing(20);

    headerLayout->addWidget(m_logout);
    m_logout->setStyleSheet(
        "QPushButton {"
        "    border: none;"
        "    background-color: #ffffff;"
        "    color: #060606;"
        "    margin: 1px;"
        "    padding: 6px 9px;"
        "    text-align: center;"
        "    text-transform: uppercase;"
        "    border-radius: 12px;"
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

    QVBoxLayout *searchLayout = new QVBoxLayout;
    m_titleright->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    m_titleright->setStyleSheet("font-size: 24px; font-weight: bold; color: white;");
    searchLayout->addLayout(headerLayout);       // Title for the right section
    m_search->setContentsMargins(10, 20, 10, 20);
    searchLayout->addWidget(m_search);           // Search component
    searchLayout->addWidget(m_searchResultsLabel); // Label for search results
    rightSideLayout->addLayout(searchLayout);
    QVBoxLayout *deleteLayout = new QVBoxLayout;
    deleteLayout->addSpacing(20);                // Add spacing before delete button
    deleteLayout->addWidget(m_deleteButton);     // Button to delete record
    rightSideLayout->addLayout(deleteLayout);

    m_layout->addLayout(rightSideLayout);

    setLayout(m_layout);

    if (!openDatabase()) {
        QMessageBox::critical(this, "Database Connection Error", "Failed to connect to the database.");
    }

    connect(m_addToDB, &QPushButton::clicked, this, &AdminWindow::addRecordToDatabase);
    connect(m_search->getSearchInput(), &QLineEdit::textChanged, m_search, &ui::components::Search::performSearch);
    connect(m_deleteButton, &QPushButton::clicked, this, &AdminWindow::deleteRecord);

    setStyleSheet("background-color: #121212; color: white");

    QString formStyleSheet = "QLineEdit { color: white; } QLabel { color: white; } QPushButton { color: white; }";
    setStyleSheet(styleSheet() + formStyleSheet);

    QString buttonStyle = "QPushButton {"
                          "  font-size: 14px;"
                          "  padding: 5px 10px;"
                          "  border: 1px solid white;"
                          "  background-color: white;"
                          "  color: #242424;"
                          "  border-radius: 5px;"
                          " font-weight: bold;"
                          "}"
                          "QPushButton:pressed {"
                          "  background-color: #dbdbbb;"
                          "}"
                          "QPushButton:hover {"
                          "    margin: 2px;"
                          "}"
        ;
    m_addToDB->setStyleSheet(buttonStyle);
    m_deleteButton->setStyleSheet(buttonStyle);
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
}


bool AdminWindow::openDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/shushan/Desktop/logindb.db");

    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
        qDebug() << db.lastError().text();
        return false;
    } else {
        qDebug() << "Database: connection ok";
        return true;
    }
}

void AdminWindow::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void AdminWindow::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        foreach (const QUrl &url, mimeData->urls()) {
            QString filePath = url.toLocalFile();
            QFileInfo fileInfo(filePath);
            if (fileInfo.suffix().toLower() == "mp3" || fileInfo.suffix().toLower() == "wav") {
                handleFileDrop(filePath);
            } else if (fileInfo.suffix().toLower() == "png" || fileInfo.suffix().toLower() == "jpg") {
                handleImageDrop(filePath);
            }
        }
    }
}

void AdminWindow::handleFileDrop(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        m_audioStatusLabel->setText("Failed to open audio file.");
        return;
    }

    m_audioData = file.readAll();
    m_audioStatusLabel->setText("Audio file loaded from: " + filePath);
    m_fileNameEdit->setText(QFileInfo(filePath).fileName());
}

void AdminWindow::handleImageDrop(const QString &filePath) {
    QPixmap image(filePath);
    if (image.isNull()) {
        m_audioStatusLabel->setText("Failed to load image file.");
        return;
    }

    m_currentImage = image;
    m_imageLabel->setPixmap(image);
}

void AdminWindow::addRecordToDatabase() {
    QString title = m_titleEdit->text();
    QString artist = m_artistEdit->text();
    QString album = m_albumEdit->text();
    QString fileName = m_fileNameEdit->text();
    QString genre = m_genreEdit->text();

    if (title.isEmpty() || artist.isEmpty() || album.isEmpty() || fileName.isEmpty() || genre.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO music (title, artist, album, file_name, genre, music, image) "
                  "VALUES (:title, :artist, :album, :file_name, :genre, :music, :image)");
    query.bindValue(":title", title);
    query.bindValue(":artist", artist);
    query.bindValue(":album", album);
    query.bindValue(":file_name", fileName);
    query.bindValue(":genre", genre);
    query.bindValue(":music", m_audioData);
    query.bindValue(":image", imageToByteArray(m_currentImage));

    if (!query.exec()) {
        QMessageBox::warning(this, "Database Error", "Failed to add record to the database.");
        qDebug() << "Database error:" << query.lastError().text();
    } else {
        QMessageBox::information(this, "Success", "Record added to the database.");
        clearFields();
    }
}


void AdminWindow::deleteRecord() {
    // Get the search query from the search line edit
    QString searchQuery = m_search->getSearchInput()->text();
    if (searchQuery.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a search term.");
        return;
    }

    // Prepare the delete query
    QSqlQuery query;
    query.prepare("DELETE FROM music WHERE title LIKE :search OR artist LIKE :search OR genre LIKE :search");
    query.bindValue(":search", "%" + searchQuery + "%");

    // Execute the query
    if (!query.exec()) {
        QMessageBox::warning(this, "Database Error", "Failed to delete record(s) from the database.");
        qDebug() << "Database error:" << query.lastError().text();
    } else {
        QMessageBox::information(this, "Success", "Record(s) deleted from the database.");
        m_search->performSearch(); // Update the search results
    }
}




void AdminWindow::searchDatabase() {
    m_search->performSearch(); // Call the public slot
}

QByteArray AdminWindow::imageToByteArray(const QPixmap &pixmap) {
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    pixmap.save(&buffer, "PNG");
    return byteArray;
}

void AdminWindow::clearFields() {
    m_titleEdit->clear();
    m_artistEdit->clear();
    m_albumEdit->clear();
    m_fileNameEdit->clear();
    m_genreEdit->clear();
    m_audioData.clear();
    m_currentImage = m_defaultImage;
    m_imageLabel->setPixmap(m_defaultImage);
    m_audioStatusLabel->clear();
}*/
AdminWindow::AdminWindow(QWidget *parent)
    : QWidget(parent)
    , m_defaultImage(":/home/shushan/Desktop/spotify/resources/images/def-music.png")
    , m_layout(new QHBoxLayout(this))
    , m_audioDropLabel(new QLabel("Drop audio files here", this))
    , m_imageDropLabel(new QLabel("Drop image files here", this))
    , m_titleEdit(new QLineEdit(this))
    , m_artistEdit(new QLineEdit(this))
    , m_albumEdit(new QLineEdit(this))
    , m_fileNameEdit(new QLineEdit(this))
    , m_titleleft(new QLabel("Add to Database", this))
    , m_titleright(new QLabel("Remove from Database", this))
    , m_genreEdit(new QLineEdit(this))
    , m_addToDB(new QPushButton("Add", this))
    , m_audioStatusLabel(new QLabel(this))
    , m_searchResultsLabel(new QLabel(this))
    , m_deleteButton(new QPushButton("Delete", this))
    , m_search(new ui::components::Search())
    , m_logout(new QPushButton("Log Out"))
{
    resize(1000, 500);
    setAcceptDrops(true);

    m_audioDropLabel->setFixedSize(200, 200);
    m_imageDropLabel->setFixedSize(200, 200);

    m_audioDropLabel->setAlignment(Qt::AlignCenter);
    m_audioDropLabel->setStyleSheet("QLabel { border: 2px dashed gray; color: white; }");
    m_imageDropLabel->setAlignment(Qt::AlignCenter);
    m_imageDropLabel->setStyleSheet("QLabel { border: 2px dashed gray; color: white; }");

    m_imageLabel = new QLabel(this);
    m_imageLabel->setPixmap(m_defaultImage);
    m_imageLabel->setFixedSize(100, 100);
    m_imageLabel->setScaledContents(true);

    m_audioStatusLabel->setAlignment(Qt::AlignCenter);
    m_searchResultsLabel->setAlignment(Qt::AlignCenter);

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("Title:", m_titleEdit);
    formLayout->addRow("Artist:", m_artistEdit);
    formLayout->addRow("Album:", m_albumEdit);
    formLayout->addRow("File Name:", m_fileNameEdit);
    formLayout->addRow("Genre:", m_genreEdit);
    formLayout->setVerticalSpacing(10);
    formLayout->setContentsMargins(10, 20, 10, 20);

    QString lineEditStyle = "QLineEdit { border: 1px solid rgba(255, 255, 255, 0.5); border-radius: 5px; color: white; }";
    m_titleEdit->setStyleSheet(lineEditStyle);
    m_artistEdit->setStyleSheet(lineEditStyle);
    m_albumEdit->setStyleSheet(lineEditStyle);
    m_fileNameEdit->setStyleSheet(lineEditStyle);
    m_genreEdit->setStyleSheet(lineEditStyle);

    QVBoxLayout *leftside = new QVBoxLayout;
    m_titleleft->setAlignment(Qt::AlignLeft);
    m_titleleft->setStyleSheet("font-size: 24px; font-weight: bold; color: white; margin-bottom: 20px;");
    leftside->addWidget(m_titleleft);
    leftside->addLayout(formLayout);
    leftside->addWidget(m_imageLabel);

    QHBoxLayout *dropLayout = new QHBoxLayout;
    dropLayout->addWidget(m_audioDropLabel);
    dropLayout->addWidget(m_imageDropLabel);
    leftside->addLayout(dropLayout);

    leftside->addWidget(m_audioStatusLabel);
    leftside->addWidget(m_addToDB);
    m_layout->addLayout(leftside);

    QFrame *line = new QFrame;
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);

    QHBoxLayout *lineLayout = new QHBoxLayout;
    lineLayout->addSpacing(20);
    lineLayout->addWidget(line);
    lineLayout->addSpacing(20);
    m_layout->addLayout(lineLayout);

    // Right side layout
    QVBoxLayout *rightSideLayout = new QVBoxLayout;

    QHBoxLayout *headerLayout = new QHBoxLayout;
    headerLayout->addWidget(m_titleright);
    headerLayout->addSpacing(20);

    headerLayout->addWidget(m_logout);
    m_logout->setStyleSheet(
        "QPushButton {"
        "    border: none;"
        "    background-color: #ffffff;"
        "    color: #060606;"
        "    margin: 1px;"
        "    padding: 6px 9px;"
        "    text-align: center;"
        "    text-transform: uppercase;"
        "    border-radius: 12px;"
        "    font-weight: bold;"
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

    QVBoxLayout *searchLayout = new QVBoxLayout;
    m_titleright->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    m_titleright->setStyleSheet("font-size: 24px; font-weight: bold; color: white;");
    searchLayout->addLayout(headerLayout);       // Title for the right section
    m_search->setContentsMargins(10, 20, 10, 20);
    searchLayout->addWidget(m_search);           // Search component
    searchLayout->addWidget(m_searchResultsLabel); // Label for search results
    rightSideLayout->addLayout(searchLayout);
    QVBoxLayout *deleteLayout = new QVBoxLayout;
    deleteLayout->addSpacing(20);                // Add spacing before delete button
    deleteLayout->addWidget(m_deleteButton);     // Button to delete record
    rightSideLayout->addLayout(deleteLayout);

    m_layout->addLayout(rightSideLayout);

    setLayout(m_layout);

    if (!openDatabase()) {
        QMessageBox::critical(this, "Database Connection Error", "Failed to connect to the database.");
    }

    connect(m_addToDB, &QPushButton::clicked, this, &AdminWindow::addRecordToDatabase);
    connect(m_search->getSearchInput(), &QLineEdit::textChanged, m_search, &ui::components::Search::performSearch);
    connect(m_deleteButton, &QPushButton::clicked, this, &AdminWindow::deleteRecord);
    connect(m_logout, &QPushButton::clicked, this, &AdminWindow::handleLogout);

    setStyleSheet("background-color: #121212; color: white");

    QString formStyleSheet = "QLineEdit { color: white; } QLabel { color: white; } QPushButton { color: white; }";
    setStyleSheet(styleSheet() + formStyleSheet);

    QString buttonStyle = "QPushButton {"
                          "  font-size: 14px;"
                          "  padding: 5px 10px;"
                          "  border: 1px solid white;"
                          "  background-color: white;"
                          "  color: #242424;"
                          "  border-radius: 5px;"
                          " font-weight: bold;"
                          "}"
                          "QPushButton:pressed {"
                          "  background-color: #dbdbbb;"
                          "}"
                          "QPushButton:hover {"
                          "    margin: 2px;"
                          "}"
        ;
    m_addToDB->setStyleSheet(buttonStyle);
    m_deleteButton->setStyleSheet(buttonStyle);
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

}

bool AdminWindow::openDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/shushan/Desktop/logindb.db");

    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
        qDebug() << db.lastError().text();
        return false;
    } else {
        qDebug() << "Database: connection ok";
        return true;
    }
}

void AdminWindow::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void AdminWindow::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        foreach (const QUrl &url, mimeData->urls()) {
            QString filePath = url.toLocalFile();
            QFileInfo fileInfo(filePath);
            qDebug() << "Dropped file:" << filePath;
            if (fileInfo.suffix().toLower() == "mp3" || fileInfo.suffix().toLower() == "wav") {
                handleFileDrop(filePath);
            } else if (fileInfo.suffix().toLower() == "png" || fileInfo.suffix().toLower() == "jpg" || fileInfo.suffix().toLower() == "jpeg") {
                handleImageDrop(filePath);
            } else {
                qDebug() << "Unsupported file type:" << fileInfo.suffix();
            }
        }
    }
}

void AdminWindow::handleFileDrop(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        m_audioStatusLabel->setText("Failed to open audio file.");
        return;
    }

    m_audioData = file.readAll();
    m_audioStatusLabel->setText("Audio file loaded from: " + filePath);
    m_fileNameEdit->setText(QFileInfo(filePath).fileName());
}

void AdminWindow::handleImageDrop(const QString &filePath) {
    QPixmap image(filePath);
    if (image.isNull()) {
        m_audioStatusLabel->setText("Failed to load image file.");
        return;
    }

    m_currentImage = image;
    m_imageLabel->setPixmap(image);
    m_audioStatusLabel->setText("Image file loaded from: " + filePath);
}

void AdminWindow::addRecordToDatabase() {
    QString title = m_titleEdit->text();
    QString artist = m_artistEdit->text();
    QString album = m_albumEdit->text();
    QString fileName = m_fileNameEdit->text();
    QString genre = m_genreEdit->text();

    if (title.isEmpty() || artist.isEmpty() || album.isEmpty() || fileName.isEmpty() || genre.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO music (title, artist, album, file_name, genre, music, image) "
                  "VALUES (:title, :artist, :album, :file_name, :genre, :music, :image)");
    query.bindValue(":title", title);
    query.bindValue(":artist", artist);
    query.bindValue(":album", album);
    query.bindValue(":file_name", fileName);
    query.bindValue(":genre", genre);
    query.bindValue(":music", m_audioData);
    query.bindValue(":image", imageToByteArray(m_currentImage));

    if (!query.exec()) {
        QMessageBox::warning(this, "Database Error", "Failed to add record to the database.");
        qDebug() << "Database error:" << query.lastError().text();
    } else {
        QMessageBox::information(this, "Success", "Record added to the database.");
        clearFields();
    }
}

void AdminWindow::deleteRecord() {
    // Get the search query from the search line edit
    QString searchQuery = m_search->getSearchInput()->text();
    if (searchQuery.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a search term.");
        return;
    }

    // Prepare the delete query
    QSqlQuery query;
    query.prepare("DELETE FROM music WHERE title LIKE :search OR artist LIKE :search OR genre LIKE :search");
    query.bindValue(":search", "%" + searchQuery + "%");

    // Execute the query
    if (!query.exec()) {
        QMessageBox::warning(this, "Database Error", "Failed to delete record(s) from the database.");
        qDebug() << "Database error:" << query.lastError().text();
    } else {
        QMessageBox::information(this, "Success", "Record(s) deleted from the database.");
        m_search->performSearch(); // Update the search results
    }
}

void AdminWindow::searchDatabase() {
    m_search->performSearch(); // Call the public slot
}

QByteArray AdminWindow::imageToByteArray(const QPixmap &pixmap) {
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    pixmap.save(&buffer, "PNG");
    return byteArray;
}

void AdminWindow::clearFields() {
    m_titleEdit->clear();
    m_artistEdit->clear();
    m_albumEdit->clear();
    m_fileNameEdit->clear();
    m_genreEdit->clear();
    m_audioData.clear();
    m_currentImage = QPixmap(m_defaultImage); // Ensure it's a QPixmap, not a QString
    m_imageLabel->setPixmap(m_currentImage);
    m_audioStatusLabel->clear();
}

void AdminWindow::handleLogout() {
    this->close();
    Welcome *welcomePage = new Welcome;
    welcomePage->show();    // Show the Welcome page
}
