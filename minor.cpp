#include "minor.h"


Minor::Minor()
{
    this->dataRows = QList<dataRow>();
}

void Minor::doJob(QMap<QString,float> sills, QTableWidget *table)
{
    //Do some thing

    //this->dataRows.append(dataRow());

    this->dataRows.last().draw(table);
}
