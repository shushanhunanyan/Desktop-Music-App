#ifndef SONGINFO_H
#define SONGINFO_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include "clickablelabel.h"
#include "src/core/Database/databasemanager.h"
#include "src/ui/views/central_area/central_area_view.h"

namespace ui
{
namespace components
{

class Song : public QWidget
{
    Q_OBJECT

public:
    explicit Song(int musicId, QWidget *parent = nullptr);
    ~Song() = default;

signals:
    void clicked(int songId);

protected:
    void mousePressEvent(QMouseEvent *event) override;

public slots:
    void loadSongData(int musicId);
    void update(int id);


private:
    QVBoxLayout *m_textLayout;
    QHBoxLayout *m_layout;
    QLabel *m_titleLabel;
    QLabel *m_artistLabel;
    QLabel *m_imgLabel;
    int m_musicId;
};

} // namespace components
} // namespace ui

#endif // SONGINFO_H
