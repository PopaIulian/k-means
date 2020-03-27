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
	mustPrintBox = false;
	srand(time(NULL));

	QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"), tr("Nr. of points:"), QLineEdit::Normal);

	int k = text.toInt();

	for (int i = 0; i < k; i++)
	{
		int pozx = rand() % 1900 + 2;
		int pozy = rand() % 1000 + 2;
		points.push_back(QPoint(pozx, pozy));
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

		determineCluster();
	}
	else if (event->buttons() == Qt::RightButton)
	{
		double minDistance = DBL_MAX;
		int clusterPosition = -1;
		for (int i = 0; i < clusterPoints.size(); i++)
		{
			QPoint point(event->pos().x(), event->pos().y());
			double dist = euclidianDistance(point, clusterPoints[i].GetPosition());
			if (dist < minDistance)
			{
				minDistance = dist;
				clusterPosition = i;
			}
		}

		clusterPoints.erase(clusterPoints.begin() + clusterPosition);

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
			for (auto cluster : clusterPoints)
				cluster.ClearPointsIndex();

			QPair<QPoint, int> pair = qMakePair(QPoint(0, 0), 0);
			QVector<QPair<QPoint, int>> sumPosition(clusterPoints.size(), pair);

			for (uint i = 0; i < points.size(); i++)
			{
				double minDist = DBL_MAX;
				int  poz = -1;
				for (int j = 0; j < clusterPoints.size(); j++)
				{
					double dist = euclidianDistance(points[i], clusterPoints[j].GetPosition());
					if (dist < minDist)
					{
						minDist = dist;
						poz = j;
					}
				}
				clusterPoints[poz].AddPointIndex(i);
				sumPosition[poz].first.setX(sumPosition[poz].first.x() + points[i].x());
				sumPosition[poz].first.setY(sumPosition[poz].first.y() + points[i].y());
				sumPosition[poz].second++;
			}

			mustContinue = false;
			for (int j = 0; j < clusterPoints.size(); j++)
			{
				QPoint newPosition = sumPosition[j].first / sumPosition[j].second;
				if (newPosition == clusterPoints[j].GetPosition())
					mustContinue = true;
				clusterPoints[j].SetPosition(newPosition);
			}
		}
	}
	else if (event->key() == Qt::Key_0)
		mustPrintBox = true;
	repaint();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
	QPainter p;
	p.begin(this);

	for (int i = 0; i < points.size(); i++)
		p.drawEllipse(points[i].x() - 2.5, points[i].y() - 2.5, 5, 5);

	for (auto cluster : clusterPoints)
	{
		p.setPen(QPen(cluster.GetColor()));
		p.drawEllipse(cluster.GetPosition().x() - 5, cluster.GetPosition().y() - 5, 10, 10);

		for (auto pointIndex : cluster.GetPointsIndex())
			p.drawLine(points[pointIndex].x(), points[pointIndex].y(), cluster.GetPosition().x(), cluster.GetPosition().y());
	}


	if (mustPrintBox)
	{



		mustPrintBox = false;
	}
}


double MainWindow::euclidianDistance(QPoint point1, QPoint point2)
{
	return qSqrt(((point1.x() - point2.x())*(point1.x() - point2.x())) + ((point1.y() - point2.y())*(point1.y() - point2.y())));
}

void MainWindow::determineCluster()
{
	for (auto& cluster : clusterPoints)
		cluster.ClearPointsIndex();
	for (uint i = 0; i < points.size(); i++)
	{
		double minDist = DBL_MAX;
		int  poz = -1;
		for (int j = 0; j < clusterPoints.size(); j++)
		{
			double dist = euclidianDistance(points[i], clusterPoints[j].GetPosition());
			if (dist < minDist)
			{
				minDist = dist;
				poz = j;
			}
		}
		clusterPoints[poz].AddPointIndex(i);
	}
}
