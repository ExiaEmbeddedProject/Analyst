#include "minor.h"

struct Document{
    QString _id;
    QString _rev;
    float Accel_x;
    float Accel_y;
    float Accel_z;
    QString DateHeure;
    float Gyro_x;
    float Gyro_y;
    float Gyro_z;
    short Humidite;
    float Latitude;
    float Longitude;
    float Temperature;
    QString Journey;
};

Minor::Minor()
{
    this->dataRows = QList<Ore>();
}

void Minor::doJob(QMap<QString,float> sills, QTableWidget *table)
{
    //Do some thing

    QVariantList rows;
    QString title;

    Ore *ore = new Ore();

    foreach(QVariant row, rows)
    {
        QJsonObject object = row.toJsonObject();
        title == "";

        title += this->prospect("Temperature", "K", &ore->tempMin, &ore->tempMax, object["Temperature"].toDouble(), sills.find("tempMax").value(), sills.find("tempMin").value());

        ore->journey = QString(row["Journey"]);

        if(title != "")
        {
            ore->markedPoints.append(markedPoint(object["Latitude"].toDouble(),object["Longitude"].toDouble(),title));
        } else
        {
            ore->points.append(point(object["Latitude"].toDouble(),object["Longitude"].toDouble()));
        }
    }

    ore->createPath();
    ore->draw(table);

    this->ores.apprend(ore);
}

QString Minor::prospect(QString ore, QString unit, QPair<float,int> *oreMin, QPair<float,int> *oreMax, float value, float sillUp, float sillDown)
{
    if(value < sillDown){
        oreMin->second++;
        if(value < oreMin->first) oreMin->first = value;

        return ore + ":" + value + unit + "<br />";

    } else if(value  > sillUp)
    {
        oreMax->second++;
        if(value > oreMax->first) oreMax->first = value;

        return ore + ":" + value + unit + "<br />";
    }

    else return "";
}
