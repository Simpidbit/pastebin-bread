#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <string>
#include <unordered_map>
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
    PastePrompt *paste_prompt = nullptr;
    PostData *post_datas_p = nullptr;

private slots:
    void on_pasteBtn_released();

    void on_timeChooseComboBox_currentTextChanged(const QString &arg1);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
