#ifndef WIDGET_H
#define WIDGET_H

#include "mywidget.h"
#include <boost/shared_ptr.hpp>

class QWidget;
class PastePrompt;
class PostData;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public MyWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    PastePrompt*                    pastePrompt {nullptr};
    boost::shared_ptr<PostData>     post_datas_p {NULL};

private slots:
    void on_pasteBtn_released();
    void on_timeChooseComboBox_currentTextChanged(const QString &arg1);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
