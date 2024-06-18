#include "main_window.h"



MainWindow::MainWindow(int userId, QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* central_widget = new QWidget(this);

    QSqlDatabase db = DatabaseManager::instance()->database();
    if (!db.isOpen()) {
        qDebug() << "Database connection is not open!";
        return;
    }

    m_footer_view = new ui::views::FooterView(userId, this);

    m_central_area_view = new ui::views::CentralAreaView(userId, this);
    m_right_sidebar_view = new ui::views::RightSidebarView(userId, this);

    QHBoxLayout* center_right_layout = new QHBoxLayout();
    center_right_layout->addWidget(m_central_area_view);
    center_right_layout->addWidget(m_right_sidebar_view);

    QVBoxLayout* center_with_header_layout = new QVBoxLayout();
    m_header_view = new ui::views::HeaderView(userId, m_footer_view, this);
    center_with_header_layout->addWidget(m_header_view);
    center_with_header_layout->addLayout(center_right_layout);

    QHBoxLayout* top_layout = new QHBoxLayout();
    m_left_sidebar_view = new ui::views::LeftSidebarView(userId, this);
    top_layout->addWidget(m_left_sidebar_view);
    top_layout->addLayout(center_with_header_layout);

    QVBoxLayout* main_layout = new QVBoxLayout(central_widget);
    main_layout->addLayout(top_layout);
    main_layout->addWidget(m_footer_view);
/*
    top_layout->setStretchFactor(m_left_sidebar_view, 1);
    top_layout->setStretchFactor(center_with_header_layout, 4);

    center_right_layout->setStretchFactor(m_central_area_view, 6);
    center_right_layout->setStretchFactor(m_right_sidebar_view, 1);

    main_layout->setStretchFactor(top_layout, 5);
*/
    top_layout->setStretchFactor(m_left_sidebar_view, 1);
    top_layout->setStretchFactor(center_with_header_layout, 4);

    center_right_layout->setStretchFactor(m_central_area_view, 5); // Slightly reduce central area size
    center_right_layout->setStretchFactor(m_right_sidebar_view, 2); // Increase right sidebar size

    main_layout->setStretchFactor(top_layout, 5);
    main_layout->setStretchFactor(m_footer_view, 1);

    setCentralWidget(central_widget);
    central_widget->setStyleSheet("background-color: #000000; border-radius: 6px;");
    m_header_view->setStyleSheet("background-color: #121212; color: white; border-radius: 6px;");
    m_footer_view->setStyleSheet("color: white;");
    m_left_sidebar_view->setStyleSheet("background-color: #121212; color: white; border-radius: 6px;");
    m_central_area_view->setStyleSheet("background-color: #121212; color: white; border-radius: 6px;");
    m_right_sidebar_view->setStyleSheet("background-color: #121212; color: white; border-radius: 6px;");

    connect(m_central_area_view, &ui::views::CentralAreaView::playMusic, m_footer_view, &ui::views::FooterView::onUpdateFooter);
    connect(m_left_sidebar_view, &ui::views::LeftSidebarView::songSelected, m_footer_view, &ui::views::FooterView::onUpdateFooter);
}




