#include "point.h"

point::point()
{

}

point::point(float lat, float lng)
{
    this->lat = lat;
    this->lng = lng;
}

void point::write(QJsonObject &json) const
{
    json["lat"] = this->lat;
    json["lng"] = this->lng;
}

