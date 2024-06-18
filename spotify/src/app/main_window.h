#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QLabel>
#include <QVBoxLayout>


#include "src/ui/views/header/header_view.h"
#include "src/ui/views/left_sidebar/left_sidebar_view.h"
#include "src/ui/views/central_area/central_area_view.h"
#include "src/ui/views/right_sidebar/right_sidebar_view.h"
#include "src/ui/views/footer/footer_view.h"
#include "src/core/Database/databasemanager.h"
#include "src/ui/components/header_components.h"
#include "src/viewmodels/usercentralareaviewmodel.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int userId, QWidget *parent = nullptr);
    ~MainWindow() = default;

private:
    ui::views::HeaderView* m_header_view;
    ui::views::LeftSidebarView* m_left_sidebar_view;
    ui::views::CentralAreaView* m_central_area_view;
    ui::views::RightSidebarView* m_right_sidebar_view;
    ui::views::FooterView* m_footer_view;
};
#endif // MAINWINDOW_H
