#define DEBUG
#include "widget.h"
#include "login.h"
#include "mywidget.h"
#include "pasteprompt.h"
#include <fstream>
#include <QString>
#include <QApplication>
#include <QDebug>
#include <curl/curl.h>

int main(int argc, char *argv[])
{
    curl_global_init(CURL_GLOBAL_ALL);
    QApplication a(argc, argv);

    QString qss;
    std::ifstream ifs;
    ifs.open("../pastebin-bread/stylesheet.css", std::ios::in);
    qDebug() << ifs.is_open();
    char c;
    while ((c = ifs.get()) != EOF) {
        qss += c;
    }

    a.setStyleSheet(qss);

    Widget w;
    w.show();

    int returnValue = a.exec();
    curl_global_cleanup();
    return returnValue;
}

int main_(int argc, char *argv[])       // main() for test
{
    QApplication a(argc, argv);

    QString qss;
    std::ifstream ifs;
    ifs.open("/home/ghostworker/code/cpp/programs/pastebin-bread/stylesheet.css", std::ios::in);
    qDebug() << ifs.is_open();
    char c;
    while ((c = ifs.get()) != EOF) {
        qss += c;
    }

    a.setStyleSheet(qss);

    PastePrompt w;
    w.show();

    int returnValue = a.exec();
    return returnValue;
}
