#ifndef CENTRALAREAVIEW_H
#define CENTRALAREAVIEW_H

#include "src/ui/components/songlist.h"
#include "src/viewmodels/usercentralareaviewmodel.h"

#include <QWidget>
#include <QSqlDatabase>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QStackedWidget>



namespace ui {
namespace viewmodels {
class UserCentralAreaViewModel;
}
}
namespace ui
{
namespace views
{


class CentralAreaView : public QWidget
{
    Q_OBJECT
public:
        //    explicit CentralAreaView(int userId, ui::views::FooterView* footerView, QWidget *parent = nullptr);
    explicit CentralAreaView(int id, QWidget *parent = nullptr);
    ~CentralAreaView() = default;

public slots:
    void handleSeeAll(bool, const QString&);
    void handleSongSelection(int id);
   // void switchToUserView();

signals:
    void playMusic(int musicId);

private:
    void setupUI();
    ui::components::MainList *l1;
    ui::components::MainList *l2;
    ui::components::MainList *l3;
    QVBoxLayout *m_layout;
    QScrollArea *m_scrollArea;
    QStackedWidget *stackedWidget;
};
/*
class CentralAreaView : public QWidget
{
    Q_OBJECT
public:
    explicit CentralAreaView(int id, QWidget *parent = nullptr);

signals:
    void playMusic(int id);

private slots:
    void handleSongSelection(int id);
    void switchToUserView();
    void switchToMainView();

private:
    ui::components::MainList *l1;
    ui::components::MainList *l2;
    ui::components::MainList *l3;
    QVBoxLayout *m_layout;
    QScrollArea *m_scrollArea;
    QStackedWidget *stackedWidget;  // Add stackedWidget as a member variable
    QWidget *mainViewWidget;  // Add mainViewWidget as a member variable
    ui::viewmodels::UserCentralAreaViewModel *userViewModel;
};*/

} // namespace views
} // namespace ui


#endif // CENTRALAREAVIEW_H
