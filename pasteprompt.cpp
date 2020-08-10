#include "pasteprompt.h"
#include "ui_pasteprompt.h"

PastePrompt::PastePrompt(QWidget *parent, int parent_w, int parent_h) :
    MyWidget(parent),
    ui(new Ui::PastePrompt)
{
    ui->setupUi(this);
    this->setWindowTitle("粘贴成功");

    // 窗口移动到屏幕中央
    this->move(parent_w / 2 - this->width() / 2,
               parent_h / 2 - this->height() / 2);

    connect(this->ui->closeBtn, &QPushButton::released,
            [=]()
            {
                this->setTextBrowser("");
                this->hide();
            });

    this->__moveBtns();
}

PastePrompt::~PastePrompt()
{
    delete ui;
}

void PastePrompt::setTextBrowser(std::string content) {
    this->ui->urlBrowser->setText(QString::fromStdString(content));
}
