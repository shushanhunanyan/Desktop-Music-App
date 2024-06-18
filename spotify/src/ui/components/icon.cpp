#include "icon.h"

namespace ui {
namespace components {

CreateIcon::CreateIcon(const QPixmap &pixmap, int size, QWidget *parent)
    : QWidget(parent)
    , m_iconPixmap(pixmap)
    , m_size(size)
{
    setFixedSize(size, size);
    setIconPixmap(pixmap);
}

void CreateIcon::setIconPixmap(const QPixmap &pixmap)
{
    m_iconPixmap = pixmap.scaled(m_size, m_size, Qt::KeepAspectRatio);
    update();
}

void CreateIcon::setIconSize(int size)
{
    m_size = size;
    setFixedSize(size, size);
    setIconPixmap(m_iconPixmap);
}

void CreateIcon::setIconStyle(const QString &style)
{
    m_style = style;
    update();
}



void CreateIcon::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.drawPixmap(rect(), m_iconPixmap); // Draw the icon pixmap to fill the widget's area

    if (!m_style.isEmpty()) {
        // Draw additional styling if specified
        // For example, you can draw borders, shadows, etc.
        // painter.drawRect(rect());
        // painter.drawText(rect(), Qt::AlignCenter, "Icon Text");
    }
}

void CreateIcon::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked();
}



} // namespace components
} // namespace ui
