#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QtMath>
#include "qmath.h"
#include <float.h>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
    mustPrintBox =false;
	srand(time(NULL));

	QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"), tr("Nr. of points:"), QLineEdit::Normal);

	int k = text.toInt();

	for (int i = 0; i < k; i++)
	{
		int pozx = rand() % 1900 + 2;
		int pozy = rand() % 1000 + 2;
		points.push_back(QVector3D(pozx, pozy, -1));
	}
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		clusterPoints.push_back(QPoint(event->pos().x(), event->pos().y()));
		int r = rand() % 255;
		int g = rand() % 255;
		int b = rand() % 255;

		QColor c = QColor(r, g, b, 255);
		colors.push_front(c);

		determineCluster();
	}
    else if (event->buttons() == Qt::RightButton)
	{
		double minDistance = DBL_MAX;
		int clusterPosition = -1;
		for (int i = 0; i < clusterPoints.size(); i++)
		{
			QVector3D point(event->pos().x(), event->pos().y(), 0);
			double dist = euclidianDistance(point, clusterPoints[i]);
			if (dist < minDistance)
			{
				minDistance = dist;
				clusterPosition = i;
			}
		}

		clusterPoints.erase(clusterPoints.begin() + clusterPosition);
		colors.erase(colors.begin() + clusterPosition);

		determineCluster();
	}

	repaint();
}


void MainWindow::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape)
	{
		bool mustContinue = true;
		while (mustContinue)
		{
			QPair<QPoint, int> pair = qMakePair(QPoint(0, 0), 0);
			QVector<QPair<QPoint, int>> sumPosition(clusterPoints.size(), pair);

			for (int i = 0; i < points.size(); i++)
			{
				double minDist = DBL_MAX;
				int  poz = -1;
				for (int j = 0; j < clusterPoints.size(); j++)
				{
					double dist = euclidianDistance(points[i], clusterPoints[j]);
					if (dist < minDist)
					{
						minDist = dist;
						poz = j;
					}
				}
				points[i].setZ(poz);
				sumPosition[poz].first.setX(sumPosition[poz].first.x() + points[i].x());
				sumPosition[poz].first.setY(sumPosition[poz].first.y() + points[i].y());
				sumPosition[poz].second++;
			}

			mustContinue = false;
			for (int j = 0; j < clusterPoints.size(); j++)
			{
				QPoint newPosition = sumPosition[j].first / sumPosition[j].second;
				if (newPosition == clusterPoints[j])
					mustContinue = true;
				clusterPoints[j] = newPosition;
			}
		}
	}
    else if (event->key() == Qt::Key_0)
        mustPrintBox=true;
	repaint();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
	QPainter p;
	p.begin(this);

	for (int i = 0; i < points.size(); i++)
		p.drawEllipse(points[i].x() - 2.5, points[i].y() - 2.5, 5, 5);

	for (int i = 0; i < points.size(); i++)
	{

		int clusterPos = points[i].z();
		if (clusterPos != -1)
		{
			p.setPen(QPen(colors[clusterPos]));

			p.drawEllipse(clusterPoints[clusterPos].x() - 5, clusterPoints[clusterPos].y() - 5, 10, 10);

			p.drawLine(points[i].x(), points[i].y(), clusterPoints[clusterPos].x(), clusterPoints[clusterPos].y());
		}
	}
}


double MainWindow::euclidianDistance(QVector3D point1, QPoint point2)
{
    return qSqrt(((point1.x() - point2.x())*(point1.x() - point2.x())) + ((point1.y() - point2.y())*(point1.y() - point2.y())));
}

void MainWindow::determineCluster()
{
    for (int i = 0; i < points.size(); i++)
    {
        double minDist = DBL_MAX;
        int  poz = -1;
        for (int j = 0; j < clusterPoints.size(); j++)
        {
            double dist = euclidianDistance(points[i], clusterPoints[j]);
            if (dist < minDist)
            {
                minDist = dist;
                poz = j;
            }
        }
        points[i].setZ(poz);
    }
}
