#ifndef NEW_PLAYLIST_CREATE_H
#define NEW_PLAYLIST_CREATE_H


#include "src/ui/components/header_components.h"

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
/*
class NewPlaylistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewPlaylistDialog(QWidget *parent = nullptr);
    ~NewPlaylistDialog() = default;
    QString getPlaylistName() const;

    int isPublicPlaylist() const;
private slots:
    void onCreateButtonClicked();
    void onPrivateCreateButtonClicked();

private:
    QLineEdit *m_playlistNameEdit;
    QPushButton *m_publicButton;
    QPushButton *m_privateButton;
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_buttonsLayout;
    ui::components::Search *m_search;
    int m_isPublic;
};*/

class NewPlaylistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewPlaylistDialog(QWidget *parent = nullptr);
    ~NewPlaylistDialog() = default;
    QString getPlaylistName() const;
    int isPublicPlaylist() const;

private slots:
    void onCreateButtonClicked();
    void onPrivateCreateButtonClicked();

private:
    QLineEdit *m_playlistNameEdit;
    QPushButton *m_publicButton;
    QPushButton *m_privateButton;
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_buttonsLayout;
    int m_isPublic;
};

#endif // NEW_PLAYLIST_CREATE_H
