#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H


#include "src/ui/components/header_components.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include <QBuffer>
#include <QFile>
#include <QFileInfo>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QUrl>

class AdminWindow : public QWidget {
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = nullptr);

private slots:
    void addRecordToDatabase();
    void searchDatabase();
    void deleteRecord();
    void handleLogout();

private:
    bool openDatabase();
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void handleFileDrop(const QString &filePath);
    void handleImageDrop(const QString &filePath);
    void saveAudioFileToDatabase(const QString &filePath);
    void saveImageToDatabase(const QPixmap &image);
    QByteArray imageToByteArray(const QPixmap &pixmap);
    void clearFields();

private:
    QHBoxLayout *m_layout;
    QLabel *m_audioDropLabel;
    QLabel *m_imageDropLabel;
    QLabel *m_imageLabel;
    QLineEdit *m_titleEdit;
    QLineEdit *m_artistEdit;
    QLineEdit *m_albumEdit;
    QLineEdit *m_fileNameEdit;
    QLineEdit *m_genreEdit;
    QPushButton *m_addToDB;
    QLabel *m_audioStatusLabel;
    QLabel *m_titleleft;
    QLabel *m_titleright;

    QLineEdit *m_searchEdit;
    QLabel *m_searchResultsLabel;
    QPushButton *m_deleteButton;

    QPixmap m_defaultImage;
    QPixmap m_currentImage;
    QByteArray m_audioData;

    ui::components::Search *m_search;
    QPushButton *m_logout;

};


#endif // ADMINWINDOW_H
