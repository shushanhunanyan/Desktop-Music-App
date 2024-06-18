#include "new_playlist_create.h"



#include <QDebug>

NewPlaylistDialog::NewPlaylistDialog(QWidget *parent)
    : QDialog(parent)
    , m_playlistNameEdit(new QLineEdit(this))
    , m_publicButton(new QPushButton("Public", this))
    , m_privateButton(new QPushButton("Private", this))
    , m_mainLayout(new QVBoxLayout(this))
    , m_buttonsLayout(new QHBoxLayout())
    , m_isPublic(1)
{
    setWindowTitle("Create New Playlist");
    setFixedSize(500, 300);

    QLabel *instructionLabel = new QLabel("Give your playlist name", this);
    instructionLabel->setAlignment(Qt::AlignCenter);
    instructionLabel->setStyleSheet("QLabel { font-size: 16px; font-weight: bold; color: white; }");

    m_playlistNameEdit->setStyleSheet(
        "QLineEdit {"
        "    border: none;"
        "    background-color: transparent;"
        "    color: white;"
        "    padding: 0;"
        "    font-size: 16px;"
        "}"
        "QLineEdit:focus {"
        "    font-size: 20px;"
        "    border-bottom: 1px solid white;"
        "}"
        );

    m_playlistNameEdit->setAlignment(Qt::AlignCenter);
    m_playlistNameEdit->setFont(QFont("Arial", 30));
    m_playlistNameEdit->setMinimumHeight(50);

    m_buttonsLayout->addWidget(m_publicButton);
    m_buttonsLayout->addWidget(m_privateButton);

    QVBoxLayout *topLayout = new QVBoxLayout();
    topLayout->addWidget(instructionLabel);
    topLayout->addStretch(); // Add stretch to center the line edit vertically
    topLayout->addWidget(m_playlistNameEdit);
    topLayout->addStretch(); // Add stretch to center the line edit vertically
    topLayout->setAlignment(Qt::AlignHCenter);

    m_mainLayout->addLayout(topLayout);
    m_mainLayout->addLayout(m_buttonsLayout);

    connect(m_publicButton, &QPushButton::clicked, this, &NewPlaylistDialog::onCreateButtonClicked);
    connect(m_privateButton, &QPushButton::clicked, this, &NewPlaylistDialog::onPrivateCreateButtonClicked);

    setLayout(m_mainLayout);
}

QString NewPlaylistDialog::getPlaylistName() const
{
    return m_playlistNameEdit->text();
}

void NewPlaylistDialog::onCreateButtonClicked()
{
    if (!m_playlistNameEdit->text().isEmpty()) {
        m_isPublic = 1; // Set to public
        accept();
    }
}

void NewPlaylistDialog::onPrivateCreateButtonClicked()
{
    if (!m_playlistNameEdit->text().isEmpty()) {
        m_isPublic = 0; // Set to private
        accept();
    }
}

int NewPlaylistDialog::isPublicPlaylist() const
{
    return m_isPublic;
}
