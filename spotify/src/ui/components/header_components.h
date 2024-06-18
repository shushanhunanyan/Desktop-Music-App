#ifndef HEADER_COMPONENTS_H
#define HEADER_COMPONENTS_H

#include "src/ui/views/footer/footer_view.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QIcon>
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlDatabase>

namespace ui {
namespace components {

class Search : public QWidget {
    Q_OBJECT

public:
    Search(ui::views::FooterView* footerView, QWidget *parent = nullptr);
    Search(QWidget *parent = nullptr);

    bool initializeDatabase();
    void performSearch();

    QLineEdit* getSearchInput() const { return searchInput; }
    QListWidget* getResultList() const { return resultList; }

signals:
    void updateFooter(int);

public slots:
    void handleResultItemClick(QListWidgetItem* item);

private:
    QLineEdit *searchInput;
    QListWidget *resultList;
    QWidget *resultContainer;
    ui::views::FooterView* m_footerView;
    void constract();
};

} // namespace components
} // namespace ui

#endif // HEADER_COMPONENTS_H
