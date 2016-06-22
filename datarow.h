#ifndef DATAROW_H
#define DATAROW_H

#include "point.h"
#include "markedPoint.h"
#include "QTableWidget"

class dataRow
{
    public:
        dataRow();
        dataRow(QList<point> points, QList<markedPoint> markedPoints, QList<QPair<float,int>> sillsExceeded, QString journey);
        void draw(QTableWidget *table);

    private:
        QList<QPair<float,int>> sillsExceeded;
        QString journey;
};

#endif // DATAROW_H
