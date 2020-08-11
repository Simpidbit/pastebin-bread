#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class QPushButton;
class QPoint;
class QSystemTrayIcon;

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

    void hideSysTrayIcon() const noexcept;

protected:
    QPushButton *_closeBtn  {nullptr};
    QPushButton *_hideBtn   {nullptr};

    QPoint *_beginPoint         {nullptr};
    QPoint *_beginCursorPoint   {nullptr};

    QSystemTrayIcon *_sysTrayIcon {nullptr};

    void mousePressEvent(QMouseEvent *event) noexcept;
    void mouseMoveEvent(QMouseEvent *event) noexcept;
    void _moveBtns() const noexcept;

private:
    Ui::MyWidget *ui;
};

#endif // MYWIDGET_H
