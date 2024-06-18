#ifndef HEADERVIEW_H
#define HEADERVIEW_H

#include "src/ui/components/header_components.h"
#include "src/ui/views/footer/footer_view.h"

#include <QWidget>
#include <QPushButton>

namespace ui
{
namespace views
{

class HeaderView : public QWidget
{
    Q_OBJECT
public:
 //   explicit HeaderView(int id, QWidget *parent = nullptr);

    explicit HeaderView(int id, ui::views::FooterView* footerView,  QWidget *parent = nullptr);
    ~HeaderView() = default;

        ui::components::Search* getSearchComponent() const {
            return m_search;
        }
private slots:
        void handleLogout();
private:
    components::Search *m_search;
    QHBoxLayout *m_layout;
    QPushButton *m_logoutButton;
signals:
};

} // namespace views
} // namespace ui

#endif // HEADERVIEW_H
