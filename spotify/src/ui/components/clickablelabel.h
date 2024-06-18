#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    explicit ClickableLabel(const QString &text, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    explicit ClickableLabel(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickableLabel();

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // CLICKABLELABEL_H
