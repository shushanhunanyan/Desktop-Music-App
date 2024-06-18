#include "clickablelabel.h"

ClickableLabel::ClickableLabel(const QString &text, QWidget* parent, Qt::WindowFlags f)
    : QLabel(text, parent, f) {
    // Additional initialization if needed
}

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent)
{
}



ClickableLabel::~ClickableLabel()
{
}

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked();
    QLabel::mousePressEvent(event);
}
