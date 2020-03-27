#pragma once
#include<QPainter>
#include<QMouseEvent>
#include<QKeyEvent>
#include<QVector>
#include<QPoint>
#include <stdlib.h>
#include <time.h>
#include <QVector3D>
#include <QSet>

class Cluster
{
public:
	Cluster();
	Cluster(const QPoint&  position);
	~Cluster();

public:
	const QSet<uint>& GetPointsIndex() const;
	QColor GetColor() const;
	QPoint GetPosition() const;
	void SetPosition(const QPoint & position);
	void AddPointIndex(uint index);
	void ClearPointsIndex();

private:
	QSet<uint> pointsIndex;
	QColor color;
	QPoint position;
};

