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

    closeBtn->resize(30, 30);
    hideBtn->resize(30, 30);

    closeBtn->setIcon(QIcon(QPixmap(":/uiimg/close.png")));
    hideBtn->setIcon(QIcon(QPixmap(":/uiimg/hide.png")));

    this->setWindowFlag(Qt::FramelessWindowHint);

    this->sysTrayIcon = new QSystemTrayIcon(this);
    this->sysTrayIcon->setIcon(QIcon(QPixmap(":/uiimg/systrayicon.jpg")));
    this->sysTrayIcon->setToolTip("Pastebin bread");
    //this->sysTrayIcon->show();

    connect(this->sysTrayIcon, &QSystemTrayIcon::activated,
            [=](QSystemTrayIcon::ActivationReason reason)
            {
                if (reason == QSystemTrayIcon::Trigger) {
                    this->show();
                    this->sysTrayIcon->hide();
                }
            }
    );

    connect(this->closeBtn, &QPushButton::released,
            [=]()
            {
                this->close();
                this->sysTrayIcon->hide();
            }
    );

    connect(this->hideBtn, &QPushButton::released,
            [=]()
            {
                this->hide();
                this->sysTrayIcon->show();
            }
    );
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "press";
    this->is_press = true;

    this->beginPoint = this->pos();
    this->beginCursorPoint = event->globalPos();

    QWidget::mousePressEvent(event);
}

void MyWidget::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "move";

    this->move(this->beginPoint + (event->globalPos() - this->beginCursorPoint));

    QWidget::mouseMoveEvent(event);
}

void MyWidget::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "release";
    this->is_press = false;
    QWidget::mouseReleaseEvent(event);
}

void MyWidget::__moveBtns()
{
    this->closeBtn->move(this->width() - closeBtn->width(), 0);
    this->hideBtn->move(this->width() - closeBtn->width() - hideBtn->width() - 1, 0);
}
