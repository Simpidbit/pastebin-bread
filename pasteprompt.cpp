#include "pasteprompt.h"
#include "ui_pasteprompt.h"

PastePrompt::PastePrompt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PastePrompt)
{
    ui->setupUi(this);
}

PastePrompt::~PastePrompt()
{
    delete ui;
}
