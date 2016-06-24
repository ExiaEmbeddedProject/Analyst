#ifndef MINOR_H
#define MINOR_H
#include "QMap.h"
#include "QTableWidget.h"
#include "ore.h"
#include "markedpoint.h"
#include "QLabel"
#include "QThread"


class Minor : public QThread
{
    Q_OBJECT

protected:
    void run();

    public:
        Minor();
        void mine(QMap<QString,float> sills, QTableWidget *table);
        QMap<QString,float> sills;
        QTableWidget *table;
        QLabel *processLabel;

    signals:
        void setVisibleText(bool);

    private:
        QString prospect(QString ore, QString unit, QPair<float,int> *oreMin, QPair<float,int> *oreMax, float value, float sillUp, float sillDown);
};

#endif // MINOR_H
