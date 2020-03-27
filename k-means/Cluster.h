#pragma once
#include<QPainter>
#include<QMouseEvent>
#include<QKeyEvent>
#include<QVector>
#include<QPoint>
#include <stdlib.h>
#include <time.h>
#include <QVector3D>

class Cluster
{
public:
	Cluster();
	Cluster(const QPoint&  position);
	~Cluster();

public:
    const QVector<uint>& GetPointsIndex() const;
    QColor GetColor() const;
    QPoint GetPosition() const;
    void SetPosition(const QPoint & position);

private:
    QVector<uint> pointsIndex;
    QColor color;
    QPoint position;
};

