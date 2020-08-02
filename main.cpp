#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    curl_global_init(CURL_GLOBAL_ALL);
    QApplication a(argc, argv);
    Widget w;
    w.show();
    int returnValue = a.exec();
    curl_global_cleanup();
    return returnValue;
}
