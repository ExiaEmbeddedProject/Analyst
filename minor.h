#ifndef MINOR_H
#define MINOR_H
#include "QMap.h"
#include "QTableWidget.h"
#include "ore.h"
#include "markedpoint.h"


class Minor
{
    public:
        Minor();
        void mine(QMap<QString,float> sills, QTableWidget *table);

    private:
        QList<Ore> ores;
        QString prospect(QString ore, QString unit, QPair<float,int> *oreMin, QPair<float,int> *oreMax, float value, float sillUp, float sillDown);
};

#endif // MINOR_H
