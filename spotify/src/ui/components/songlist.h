#ifndef SONGLIST_H
#define SONGLIST_H

#include <QString>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMouseEvent>
#include <QPushButton>


namespace ui {
namespace components {

class List : public QWidget
{
    Q_OBJECT

public:
    List(int id, QWidget *parent = nullptr);
    ~List() = default;
    void loadData(int);

signals:
    void listClicked(int id);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    int m_id;  // Store the id
    QLabel *m_title;
    QLabel *m_img_lbl;
    QVBoxLayout *m_layout;
    QWidget *m_container;
};



class MainList : public QWidget {
    Q_OBJECT
public:
    explicit MainList(const QString &genre, QWidget *parent = nullptr);
    ~MainList() = default;

signals:
    void listClicked(int id);
    void seeAllClicked(const QString &genre);

private slots:
    void handleSeeAll();
    void handleListClicked(int id);

private:
    QHBoxLayout *m_layout;
    QLabel *m_title_genre;
 //   QPushButton *m_seeAll;
    List *m_l1;
    List *m_l2;
    List *m_l3;
    List *m_l4;
    List *m_l5;

};


}
}

#endif // SONGLIST_H
