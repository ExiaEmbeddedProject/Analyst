#include "ore.h"
#include "tools.h"
#include <QApplication>

Ore::Ore()
{
    this->tempMin = QPair<float,int>(0,0);
    this->tempMax = QPair<float,int>(0,0);

    this->humiMin = QPair<float,int>(0,0);
    this->humiMax = QPair<float,int>(0,0);

    this->accelMin = QPair<float,int>(0,0);
    this->accelMax = QPair<float,int>(0,0);

    this->gyroMin = QPair<float,int>(0,0);
    this->gyroMax = QPair<float,int>(0,0);

    this->points = QList<point>();
    this->markedPoints = QList<markedPoint>();
}

Ore::Ore(QList<point> points, QList<markedPoint> markedPoints, QList<QPair<float,int>> sillsExceeded, QString journey)
{
    this->journey = journey;
    this->sillsExceeded = sillsExceeded;
}

void Ore::draw(QTableWidget *table)
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

void Ore::createPath()
{
    Tools::writeJsonFile(QApplication::applicationDirPath() + "/" + journey +".json", Tools::createJsonObject(points, markedPoints));
}
