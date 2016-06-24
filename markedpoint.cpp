#include "markedpoint.h"

markedPoint::markedPoint()
{

}


markedPoint::markedPoint(float lat, float lng, QString title, QString content)
{
    this->lat = lat;
    this->lng = lng;
    this->title = title;
    this->content = content;
}

void markedPoint::write(QJsonObject &json) const
{
    point::write(json);
    json["title"] = this->title;
    json["content"] = this->content;
}
