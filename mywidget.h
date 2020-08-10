#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QPoint>
#include <QSystemTrayIcon>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

protected:
    QPushButton *_closeBtn{new QPushButton(this)};
    QPushButton *_hideBtn{new QPushButton(this)};

    QPoint _beginPoint;
    QPoint _beginCursorPoint;

    QSystemTrayIcon *_sysTrayIcon;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void _moveBtns();

private:
    Ui::MyWidget *ui;
};

#endif // MYWIDGET_H
