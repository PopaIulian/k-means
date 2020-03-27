#include "Cluster.h"
#include <stdlib.h>
#include <time.h>

//srand(time(NULL));

Cluster::Cluster()
{
}

Cluster::Cluster(const QPoint& clusterPosition)
	: m_position(clusterPosition)
{
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;

	m_color = QColor(r, g, b, 255);

	m_boundingBox = QPair<QPoint, QPoint>( QPoint(INT_MAX, INT_MAX), QPoint(-1, -1));
}


Cluster::~Cluster()
{
}

const QSet<uint>& Cluster::GetPointsIndex() const
{
	return m_pointsIndex;
}

QColor Cluster::GetColor() const
{
	return m_color;
}

QPoint Cluster::GetPosition() const
{
	return m_position;
}

void Cluster::SetPosition(const QPoint &pos)
{
	m_position = pos;
}

void Cluster::AddPointIndex(uint pointIndex, QPoint pointPosition)
{
	m_pointsIndex.insert(pointIndex);
	
	if (pointPosition.x() < m_boundingBox.first.x())
		m_boundingBox.first.setX(pointPosition.x());
	if (pointPosition.y() < m_boundingBox.first.y())
		m_boundingBox.first.setY(pointPosition.y());	

	if (pointPosition.x() > m_boundingBox.second.x())
		m_boundingBox.second.setX(pointPosition.x());
	if (pointPosition.y() > m_boundingBox.second.y())
		m_boundingBox.second.setY(pointPosition.y());
}



void Cluster::ClearPointsIndex()
{
	m_pointsIndex.clear();
	m_boundingBox = QPair<QPoint, QPoint>(QPoint(INT_MAX, INT_MAX), QPoint(-1, -1));
}

double Cluster::GetDensity() const
{
	int l = m_boundingBox.second.x() - m_boundingBox.first.x();
	int L = m_boundingBox.second.y() - m_boundingBox.first.y();
	double nrOfPoints = m_pointsIndex.size();
	double area = L * l;
	return nrOfPoints/area;
}

const QPair<QPoint, QPoint>& Cluster::GetBoundingBox() const
{
	return m_boundingBox;
}
