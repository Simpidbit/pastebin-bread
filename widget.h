#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <string>
#include "pasteprompt.h"
#include "sendpost.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    std::string response_url;

private slots:
    void on_pasteBtn_released();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
