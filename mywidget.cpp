#include "mywidget.h"
#include "ui_mywidget.h"
#include <QPoint>
#include <QDebug>
#include <QMouseEvent>
#include <QApplication>
#include <QSystemTrayIcon>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    this->_closeBtn->resize(30, 30);
    this->_hideBtn->resize(30, 30);

    this->_closeBtn->setIcon(QIcon(QPixmap(":/uiimg/close.png")));
    this->_hideBtn->setIcon(QIcon(QPixmap(":/uiimg/hide.png")));

    this->setWindowFlag(Qt::FramelessWindowHint);

    this->_sysTrayIcon = new QSystemTrayIcon(this);
    this->_sysTrayIcon->setIcon(QIcon(QPixmap(":/uiimg/systrayicon.jpg")));
    this->_sysTrayIcon->setToolTip("Pastebin bread");
    //this->_sysTrayIcon->show();

    connect(this->_sysTrayIcon, &QSystemTrayIcon::activated,
            [=](QSystemTrayIcon::ActivationReason reason)
            {
                if (reason == QSystemTrayIcon::Trigger) {
                    this->show();
                    this->_sysTrayIcon->hide();
                }
            }
    );

    connect(this->_closeBtn, &QPushButton::released,
            [=]()
            {
                this->close();
                this->_sysTrayIcon->hide();
            }
    );

    connect(this->_hideBtn, &QPushButton::released,
            [=]()
            {
                this->hide();
                this->_sysTrayIcon->show();
            }
    );
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::mousePressEvent(QMouseEvent *event)
{
    this->_beginPoint = this->pos();
    this->_beginCursorPoint = event->globalPos();
    QWidget::mousePressEvent(event);
}

void MyWidget::mouseMoveEvent(QMouseEvent *event)
{
    this->move(this->_beginPoint + (event->globalPos() - this->_beginCursorPoint));
    QWidget::mouseMoveEvent(event);
}

void MyWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

void MyWidget::_moveBtns()
{
    this->_closeBtn->move(this->width() - this->_closeBtn->width(), 0);
    this->_hideBtn->move(this->width() - this->_closeBtn->width() - this->_hideBtn->width() - 1, 0);
}
