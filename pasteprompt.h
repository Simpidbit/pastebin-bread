#ifndef PASTEPROMPT_H
#define PASTEPROMPT_H

#include <QWidget>
#include "mywidget.h"

namespace Ui {
class PastePrompt;
}

class PastePrompt : public MyWidget
{
    Q_OBJECT

public:
    explicit PastePrompt(QWidget *parent = nullptr, int parent_w = 0, int parent_h = 0);
    ~PastePrompt();

    void setTextBrowser(std::string);

private:
    Ui::PastePrompt *ui;
};

#endif // PASTEPROMPT_H
