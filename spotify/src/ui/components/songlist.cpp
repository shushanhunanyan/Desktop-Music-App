#include "songlist.h"
#include "src/core/Database/databasemanager.h"
#include "src/ui/views/footer/footer_view.h"
#include "src/ui/views/central_area/central_area_view.h"

#include <QMouseEvent>

namespace ui {
namespace components {


List::List(int id, QWidget *parent)
    : QWidget(parent), m_id(id)
    , m_title(new QLabel(this))
    , m_img_lbl(new QLabel(this))
    , m_layout(new QVBoxLayout())
    , m_container(new QWidget(this))
{
    m_title->setStyleSheet("QLabel { color: white; border: none; }");

    m_img_lbl->setScaledContents(false); // Do not scale the content directly
    m_img_lbl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // Allow expansion
    m_img_lbl->setMaximumSize(300, 370); // Max size for the image
    m_img_lbl->setMinimumSize(130, 200); // Min size for the image
    m_img_lbl->setAlignment(Qt::AlignCenter);

    m_layout->addWidget(m_img_lbl);
    m_layout->addWidget(m_title);

    m_container->setLayout(m_layout);
    m_layout->setStretch(0, 1);
    m_layout->setStretch(1, 0);

    setLayout(new QVBoxLayout());
    layout()->addWidget(m_container);

    loadData(id);
}

void List::mousePressEvent(QMouseEvent *event) {
    Q_UNUSED(event);
    emit listClicked(m_id);
}

void List::loadData(int id) {
    QSqlDatabase db = DatabaseManager::instance()->database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Failed to connect to the database.");
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT title, image FROM music WHERE music_id = :music_id");
    query.bindValue(":music_id", id);

    if (!query.exec()) {
        qDebug() << "Error loading song data:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        QString title = query.value("title").toString();
        m_title->setText(title);

        QByteArray picData = query.value("image").toByteArray();
        QPixmap profilePixmap;
        if (!profilePixmap.loadFromData(picData)) {
            profilePixmap.load(":/resources/images/profile_pic.jpg");
        }

        // Scale the pixmap while keeping aspect ratio
        QSize labelSize = m_img_lbl->size();
        QPixmap scaledPixmap = profilePixmap.scaled(labelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        m_img_lbl->setPixmap(scaledPixmap);

        m_img_lbl->setStyleSheet("border: 3px solid #444; padding: 10px; background-color: #222;");
    }
}

MainList::MainList(const QString &genre, QWidget *parent)
    : QWidget(parent)
    , m_layout{new QHBoxLayout()}
    , m_title_genre{new QLabel(genre)}
   // , m_seeAll{new QPushButton("See All")}
{
    if (genre == "Popular") {
        m_l1 = new List(1, this);
        m_l2 = new List(2, this);
        m_l3 = new List(3, this);
        m_l4 = new List(4, this);
        m_l5 = new List(5, this);
    } else if (genre == "Shuffle") {
        m_l1 = new List(6, this);
        m_l2 = new List(7, this);
        m_l3 = new List(8, this);
        m_l4 = new List(9, this);
        m_l5 = new List(10, this);
    }

 //   m_seeAll->setStyleSheet("QLabel { color: white; border: none; font-weight: bold;}");
    m_title_genre->setStyleSheet("QLabel { color: white; border: none; font-weight: bold;}");
    QHBoxLayout *sectiontext = new QHBoxLayout();
    sectiontext->addWidget(m_title_genre);
    sectiontext->addStretch();
 //   sectiontext->addWidget(m_seeAll);

    m_layout->addWidget(m_l1);
    m_layout->addWidget(m_l2);
    m_layout->addWidget(m_l3);
    m_layout->addWidget(m_l4);
    m_layout->addWidget(m_l5);

    QVBoxLayout *together = new QVBoxLayout();
    together->addLayout(sectiontext);
    together->addLayout(m_layout);

    setLayout(together);
/*
    connect(m_l1, &List::listClicked, this, &MainList::handleListClicked);
    connect(m_l2, &List::listClicked, this, &MainList::handleListClicked);
    connect(m_l3, &List::listClicked, this, &MainList::handleListClicked);
    connect(m_l4, &List::listClicked, this, &MainList::handleListClicked);
    connect(m_l5, &List::listClicked, this, &MainList::handleListClicked);

    connect(m_seeAll, &QPushButton::clicked, this, &MainList::handleSeeAll);
*/
    connect(m_l1, &List::listClicked, this, &MainList::listClicked);
    connect(m_l2, &List::listClicked, this, &MainList::listClicked);
    connect(m_l3, &List::listClicked, this, &MainList::listClicked);
    connect(m_l4, &List::listClicked, this, &MainList::listClicked);
    connect(m_l5, &List::listClicked, this, &MainList::listClicked);
}


void MainList::handleSeeAll()
{
qDebug() << "yasss to hhven";
 //   emit seeAllClicked(m_title_genre->text());
}

void MainList::handleListClicked(int id)
{
  //  emit listItemClicked(id);
}

} // namespace components
} // namespace ui
