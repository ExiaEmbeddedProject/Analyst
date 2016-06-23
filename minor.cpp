#include "minor.h"
#include "couchdb.h"
#include "sstream"

Minor::Minor()
{
    this->ores = QList<Ore>();
}

void Minor::mine(QMap<QString,float> sills, QTableWidget *table)
{
    //Do some thing

    QVariantList rows;
    QString title;

    Ore *ore = new Ore();

    foreach(QJsonValue row, Couchdb::documents)
    {
        QJsonObject object = row.toObject()["value"].toObject();

        title = "";
        title += this->prospect("Temperature", "K", &ore->tempMin, &ore->tempMax, object["temperature"].toDouble(), sills.find("tempMax").value(), sills.find("tempMin").value());
        //title += this->prospect("Humidity", "%", &ore->humiMin, &ore->humiMax, object["humidity"].toDouble(), sills.find("humiMax").value(), sills.find("humiMin").value());


        ore->journey = QString(row.toObject()["key"].toString());

        if(title != "")
        {
            ore->markedPoints.append(markedPoint(object["latitude"].toDouble(),object["longitude"].toDouble(),title));
        } else
        {
            ore->points.append(point(object["latitude"].toDouble(),object["longitude"].toDouble()));
        }
    }

    ore->createPath();
    ore->draw(table);

    this->ores.append(*ore);
}

QString Minor::prospect(QString ore, QString unit, QPair<float,int> *oreMin, QPair<float,int> *oreMax, float value, float sillUp, float sillDown)
{
    if(value < sillDown){
        oreMin->second++;
        if(value < oreMin->first) oreMin->first = value;

        return ore + ":" + QString::number(value) + unit + "<br />";

    } else if(value  > sillUp)
    {
        oreMax->second++;
        if(value > oreMax->first) oreMax->first = value;

        return ore + ":" + QString::number(value) + unit + "<br />";
    }

    else return "";
}
