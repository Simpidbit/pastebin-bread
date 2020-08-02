#ifndef PASTEPROMPT_H
#define PASTEPROMPT_H

#include <QWidget>

namespace Ui {
class PastePrompt;
}

class PastePrompt : public QWidget
{
    Q_OBJECT

public:
    explicit PastePrompt(QWidget *parent = nullptr);
    ~PastePrompt();

private:
    Ui::PastePrompt *ui;
};

#endif // PASTEPROMPT_H
