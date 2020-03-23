#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand (time(NULL));

    //QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),tr("Nr. of points:"), QLineEdit::Normal);

   int k=50;//text.toInt();

    for(int i=0;i<k;i++)
    {
        int pozx = rand() % 500 + 2;

        int pozy = rand() % 500 + 2;
        points.push_back(QPoint(pozx,pozy));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                            tr("Nr. of cluser:"), QLineEdit::Normal);

   int k=text.toInt();
   for(int i=0;i<k;i++)
   {
       int pozx = rand() % 500 + 2;

       int pozy = rand() % 500 + 2;
       clusterPoints.push_back(QPoint(pozx,pozy));
   }
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

    for(int i=0;i<points.size();i++)
        p.drawEllipse(points[i].x(),points[i].y(),5,5);


    for(int i=0;i<clusterPoints.size();i++)
       {
        int r = rand() % 255;
        int g = rand() % 255;
        int b = rand() % 255;

        QColor c=QColor(r,g,b, 255);
        p.setPen(QPen(c));

        p.drawEllipse(clusterPoints[i].x(),clusterPoints[i].y(),10,10);
    }
}
