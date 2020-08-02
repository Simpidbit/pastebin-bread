#include "widget.h"
#include "ui_widget.h"
#include "sendpost.h"
#include <QDebug>
#include <string>
#include <QClipboard>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pasteBtn_released()
{
    /* Get paste conten */
    std::string paste_content = ui->pMainEdit->toPlainText().toStdString();
    qDebug() << "Hello world";
    std::string resulturl = sendPostMsg((std::string)"api_dev_key=_oEOdQg9gJEe786KEgIyH5ssC0v4l7ij&api_option=paste&api_paste_code=" + paste_content);
    qDebug() << "Hi world";

    QClipboard *clipboard = QApplication::clipboard();
    QString originalText = QString::fromStdString(resulturl);
    clipboard->setText(originalText);
}
