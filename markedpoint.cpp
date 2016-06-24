#include "markedpoint.h"

markedPoint::markedPoint()
{

}


markedPoint::markedPoint(float lat, float lng, QString title, QString info)
{
    this->lat = lat;
    this->lng = lng;
    this->title = title;
    this->info = info;
}

void markedPoint::write(QJsonObject &json) const
{
    point::write(json);
    json["title"] = this->title;
    json["info"] = this->info;
}
