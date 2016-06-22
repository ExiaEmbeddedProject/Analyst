#ifndef MINOR_H
#define MINOR_H
#include "QMap.h"
#include "QTableWidget.h"
#include "datarow.h"


class Minor
{
    public:
        Minor();
        void doJob(QMap<QString,float> sills, QTableWidget *table);

    private:
        QList<dataRow> dataRows;
};

#endif // MINOR_H
