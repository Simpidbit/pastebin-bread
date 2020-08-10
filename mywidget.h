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
    QPushButton *closeBtn{new QPushButton(this)};
    QPushButton *hideBtn{new QPushButton(this)};

    bool is_press{false};
    QPoint beginPoint;
    QPoint beginCursorPoint;

    QSystemTrayIcon *sysTrayIcon;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void __moveBtns();

private:
    Ui::MyWidget *ui;
};

#endif // MYWIDGET_H
