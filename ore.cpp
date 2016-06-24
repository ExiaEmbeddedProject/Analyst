#include "ore.h"
#include "tools.h"
#include <QApplication>

Ore::Ore()
{
    this->sillsExceeded = QList<QPair<float,int>*>();
    this->tempMin = QPair<float,int>(0,0);
    this->tempMax = QPair<float,int>(0,0);

    this->humiMin = QPair<float,int>(0,0);
    this->humiMax = QPair<float,int>(0,0);

    this->accelMin = QPair<float,int>(0,0);
    this->accelMax = QPair<float,int>(0,0);

    this->gyroMin = QPair<float,int>(0,0);
    this->gyroMax = QPair<float,int>(0,0);

    this->sillsExceeded.append(&this->tempMin);
    this->sillsExceeded.append(&this->tempMax);
    this->sillsExceeded.append(&this->humiMin);
    this->sillsExceeded.append(&this->humiMax);
    this->sillsExceeded.append(&this->accelMin);
    this->sillsExceeded.append(&this->accelMax);
    this->sillsExceeded.append(&this->gyroMin);
    this->sillsExceeded.append(&this->gyroMax);


    this->points = QList<point>();
    this->markedPoints = QList<markedPoint>();
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
        itab->setText(QString::number(this->sillsExceeded[i]->first) + "(" + QString::number(this->sillsExceeded[i]->second) + ")");

        table->setItem(table->rowCount() - 1, i + 1, itab);

        if(this->sillsExceeded[i]->second > 0)
            table->item(table->rowCount() - 1, i + 1)->setBackground(Qt::red);
        else
            table->item(table->rowCount() - 1, i + 1)->setBackground(Qt::green);
    }
}

void Ore::createPath()
{
    Tools::writeJsonFile(QApplication::applicationDirPath() + "/" + journey +".json", Tools::createJsonObject(points, markedPoints));
}
