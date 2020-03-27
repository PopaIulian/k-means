#include "Cluster.h"
#include <stdlib.h>
#include <time.h>

//srand(time(NULL));

Cluster::Cluster()
{
}

Cluster::Cluster(const QPoint& position)
	: position(position)
{
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;

	color = QColor(r, g, b, 255);
}


Cluster::~Cluster()
{
}

const QSet<uint>& Cluster::GetPointsIndex() const
{
	return pointsIndex;
}

QColor Cluster::GetColor() const
{
	return color;
}

QPoint Cluster::GetPosition() const
{
	return position;
}

void Cluster::SetPosition(const QPoint &pos)
{
	position = pos;
}

void Cluster::AddPointIndex(uint index)
{
	pointsIndex.insert(index);
}

void Cluster::ClearPointsIndex()
{
	pointsIndex.clear();
}
