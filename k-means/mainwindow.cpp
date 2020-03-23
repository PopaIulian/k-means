#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand (time(NULL));

    for(int i=0;i<50;i++)
    {
        int pozx = rand() % 500 + 1;

        int pozy = rand() % 500 + 1;
        puncte.push_back(QPoint(pozx,pozy));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //puncte.push_back(QPoint(event->x(),event->y()));
    //repaint();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    /*if(event->key()==Qt::Key_Escape)
    {
        introducere=false;
        formeaza_conexiuni();
    }
    repaint();*/
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter p;
    p.begin(this);

    for(int i=0;i<puncte.size();i++)
        p.drawEllipse(puncte[i].x(),puncte[i].y(),5,5);

}
