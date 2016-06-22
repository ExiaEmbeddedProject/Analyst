#include "datarow.h"
#include "tools.h"
#include <QApplication>

dataRow::dataRow()
{

}

dataRow::dataRow(QList<point> points, QList<markedPoint> markedPoints, QList<QPair<float,int>> sillsExceeded, QString journey)
{
    this->journey = journey;
    this->sillsExceeded = sillsExceeded;

    tools::writeJsonFile(QApplication::applicationDirPath() + "/" + journey +".json", tools::createJsonObject(points, markedPoints));
}

void dataRow::draw(QTableWidget *table)
{
    table->insertRow( table->rowCount() );

    QTableWidgetItem *title;
    title = new QTableWidgetItem;
    title->setText(this->journey);
    table->setItem(table->rowCount() - 1, 0, title);

    for(int i = 0; i < this->sillsExceeded.count(); i++)
    {
        QTableWidgetItem *itab;
        itab = new QTableWidgetItem;
        itab->setText(QString::number(this->sillsExceeded[i].first) + "(" + QString(this->sillsExceeded[i].second) + ")");
        table->setItem(table->rowCount() - 1, i + 1, itab);
    }
}
