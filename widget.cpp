#include "widget.h"
#include "ui_widget.h"
#include "sendpost.h"
#include "pasteprompt.h"
#include "sendpost.h"

#include <string>
#include <map>
#include <utility>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <QWidget>
#include <QDebug>
#include <QClipboard>
#include <QString>
#include <QApplication>
#include <QDesktopWidget>
#include <QComboBox>
#include <QStyledItemDelegate>


static const std::vector<std::pair<QString, std::string> > timeChooser
{
    {"从不", "N"},
    {"10分钟", "10M"},
    {"1小时", "1H"},
    {"1天", "1D"},
    {"1周", "1W"},
    {"2周", "2W"},
    {"1个月", "1M"},
    {"6个月", "6M"},
    {"1年", "1Y"}
};


Widget::Widget(QWidget *parent)
    : MyWidget(parent)
    , ui(new Ui::Widget)
{
    // Must init some member pointer before ui->setupUi
    this->post_datas_p = boost::make_shared<PostData>((std::unordered_map<std::string, std::string>){ {"api_dev_key","_oEOdQg9gJEe786KEgIyH5ssC0v4l7ij"} });
    this->pastePrompt = new PastePrompt(nullptr, this->width(), this->height());


    ui->setupUi(this);
    ui->titleEdit->setText("Untitled");

    int screen_w = QApplication::desktop()->width();
    int screen_h = QApplication::desktop()->height();

    // 主窗口移动到屏幕中央
    this->move(
                screen_w / 2 - this->width() / 2,
                screen_h / 2 - this->height() / 2
                );
    this->setWindowTitle("Pastebin Bread");

    for (auto iter = timeChooser.cbegin(); iter != timeChooser.cend(); iter++) {
        ui->timeChooseComboBox->addItem(iter->first);
    }

    QStyledItemDelegate* itemDelegate = new QStyledItemDelegate();
    ui->timeChooseComboBox->setItemDelegate(itemDelegate);

    connect(this->_closeBtn, &QPushButton::released,
            [=]()
            {
                this->pastePrompt->hideSysTrayIcon();
                this->pastePrompt->close();
                this->close();
            }
    );

    this->_moveBtns();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pasteBtn_released()
{
    /* Get paste conten */
    std::string paste_content = ui->pMainEdit->toPlainText().toStdString();
    std::string paste_name = this->ui->titleEdit->text().toStdString();

    this->post_datas_p->datas["api_option"] = "paste";
    this->post_datas_p->datas["api_paste_code"] = paste_content;
    this->post_datas_p->datas["api_paste_name"] = paste_name;

    std::string post_msg_result = sendPostMsg(post_datas_p->datasToStr());

    if (post_msg_result.find("Bad API request") != std::string::npos
            || post_msg_result.find("Error: CURL* curl == NULL") != std::string::npos) {
        qDebug() << QString::fromStdString(post_msg_result);
        return;
    }


    QClipboard *clipboard = QApplication::clipboard();
    QString originalText = QString::fromStdString(post_msg_result);
    clipboard->setText(originalText);

    pastePrompt->setTextBrowser(post_msg_result);
    pastePrompt->show();
}

void Widget::on_timeChooseComboBox_currentTextChanged(const QString &arg1)
{
    for (auto iter = timeChooser.cbegin(); iter != timeChooser.cend(); iter++) {
        if (iter->first == arg1) {
            this->post_datas_p->datas["api_paste_expire_date"] = iter->second;
            break;
        }
    }
}
