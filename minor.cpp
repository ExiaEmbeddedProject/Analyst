#include "minor.h"
#include "couchdb.h"
#include "sstream"

Minor::Minor()
{

}

void Minor::run()
{
    this->mine(this->sills, this->table);

    QObject::connect(this,SIGNAL(setVisibleText(bool)),this->processLabel,SLOT(setVisible(bool)),Qt::QueuedConnection);
}

void Minor::mine(QMap<QString,float> sills, QTableWidget *table)
{
    //Do some thing

    QVariantList rows;
    QString content;
    QString journey = "";
    Ore *ore = new Ore();

    foreach(QJsonValue row, Couchdb::documents)
    {
        if(journey != QString(row.toObject()["key"].toString()))
        {
            if(journey != "")
            {
                ore->createPath();
                ore->draw(table);
            }
            ore->journey = journey = QString(row.toObject()["key"].toString());
        }

        QJsonObject object = row.toObject()["value"].toObject();

        content = "";
        content += this->prospect("Temperature", "K", &ore->tempMin, &ore->tempMax, object["temperature"].toDouble(), sills.find("tempMax").value(), sills.find("tempMin").value());
        content += this->prospect("Humidity", "%", &ore->humiMin, &ore->humiMax, object["humidity"].toDouble(), sills.find("humiMax").value(), sills.find("humiMin").value());

        content += this->prospect("Accelerometer", "m.s^-2", &ore->accelMin, &ore->accelMax, object["accelX"].toDouble(), sills.find("accelMax").value(), sills.find("accelMin").value());
        content += this->prospect("Accelerometer", "m.s^-2", &ore->accelMin, &ore->accelMax, object["accelY"].toDouble(), sills.find("accelMax").value(), sills.find("accelMin").value());
        content += this->prospect("Accelerometer", "m.s^-2", &ore->accelMin, &ore->accelMax, object["accelZ"].toDouble(), sills.find("accelMax").value(), sills.find("accelMin").value());

        content += this->prospect("Gyroscope", "degree.s", &ore->gyroMin, &ore->gyroMax, object["gyroX"].toDouble(), sills.find("gyroMax").value(), sills.find("gyroMin").value());
        content += this->prospect("Gyroscope", "degree.s", &ore->gyroMin, &ore->gyroMax, object["gyroY"].toDouble(), sills.find("gyroMax").value(), sills.find("gyroMin").value());
        content += this->prospect("Gyroscope", "degree.s", &ore->gyroMin, &ore->gyroMax, object["gyroZ"].toDouble(), sills.find("gyroMax").value(), sills.find("gyroMin").value());

        if(content != "")
        {
            ore->markedPoints.append(markedPoint(object["latitude"].toDouble(),object["longitude"].toDouble(),"UnexpectedPoint",content));
        } else
        {
            ore->points.append(point(object["latitude"].toDouble(),object["longitude"].toDouble()));
        }
    }

    ore->createPath();
    ore->draw(table);

    delete ore;
    emit setVisibleText(false);
    emit setVisibleText(false);
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

    if(value < oreMin->first) oreMin->first = value;
    if(value > oreMax->first) oreMax->first = value;

    return "";
}
