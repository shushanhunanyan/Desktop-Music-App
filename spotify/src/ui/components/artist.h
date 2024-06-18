#ifndef ARTIST_H
#define ARTIST_H

#include "src/core/Database/databasemanager.h"
#include <QMessageBox>

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

namespace ui {
namespace components {

class Artist : public QWidget
{
    Q_OBJECT
public:
    explicit Artist(int, QWidget *parent = nullptr);
    ~Artist() = default;
    void loadArtistData(int id);

private:
    QHBoxLayout *m_layout;
    QLabel *m_img_lbl;
    QLabel *m_artist_name_lbl;
};

} // namespace components
} // namespace ui

#endif // ARTIST_H
