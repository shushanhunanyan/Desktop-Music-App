#ifndef ADDTOPLAYLISTDIALOG_H
#define ADDTOPLAYLISTDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>

#include "src/core/Database/databasemanager.h"

class AddToPlaylistDialog : public QDialog {
    Q_OBJECT

public:
    AddToPlaylistDialog(int userId, int musicId, QWidget *parent = nullptr);

private slots:
    void onAddButtonClicked();

private:
    int m_userId;
    int m_musicId;
    QVBoxLayout *m_layout;
    QComboBox *m_playlistComboBox;
    QPushButton *m_addButton;
};

#endif // ADDTOPLAYLISTDIALOG_H
