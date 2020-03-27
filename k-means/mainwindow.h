#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QMouseEvent>
#include<QKeyEvent>
#include<QVector>
#include<QPoint>
#include <stdlib.h>
#include <time.h>
#include <QVector3D>
#include "Cluster.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

protected:
	virtual void mousePressEvent(QMouseEvent *event) override;
	virtual void keyPressEvent(QKeyEvent *event) override;
	virtual void paintEvent(QPaintEvent *event) override;


private:
	Ui::MainWindow *ui;


	QVector<QPoint>points;
	QVector<Cluster>clusterPoints;
	bool mustPrintBox;

private:
	double euclidianDistance(QPoint point1, QPoint point2);
	void determineCluster();
};

#endif // MAINWINDOW_H
