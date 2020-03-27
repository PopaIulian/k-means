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
	Cluster(const QPoint& clusterPosition);
	~Cluster();

public:
	const QSet<uint>& GetPointsIndex() const;
	QColor GetColor() const;
	QPoint GetPosition() const;
	void SetPosition(const QPoint & position);
	void AddPointIndex(uint pointIndex, QPoint pointPosition);
	void ClearPointsIndex();
	double GetDensity() const;
	const QPair<QPoint, QPoint>& GetBoundingBox() const;

private:
	QSet<uint> m_pointsIndex;
	QColor m_color;
	QPoint m_position;
	QPair<QPoint, QPoint> m_boundingBox;
};

