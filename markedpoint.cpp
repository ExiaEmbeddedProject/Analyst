#include "markedpoint.h"

markedPoint::markedPoint()
{

}


markedPoint::markedPoint(float lat, float lng, QString title)
{
    this->lat = lat;
    this->lng = lng;
    this->title = title;
}

void markedPoint::write(QJsonObject &json) const
{
    point::write(json);
    json["title"] = this->title;
}
