#ifndef DATAROW_H
#define DATAROW_H

#include "point.h"
#include "markedPoint.h"
#include "QTableWidget"

class Ore
{
    public:
        Ore();
        void draw(QTableWidget *table);
        void createPath();
        QString journey;

        QList<point> points;
        QList<markedPoint> markedPoints;

        QPair<float,int> tempMin;
        QPair<float,int> tempMax;

        QPair<float,int> humiMin;
        QPair<float,int> humiMax;

        QPair<float,int> accelMin;
        QPair<float,int> accelMax;

        QPair<float,int> gyroMin;
        QPair<float,int> gyroMax;
};

#endif // DATAROW_H
