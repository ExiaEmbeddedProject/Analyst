#ifndef POINT_H
#define POINT_H
#include <QJsonObject.h>


class point
{
    public:
        point();
        point(float lat, float lng);
        float lat;
        float lng;
        void write(QJsonObject &json) const;
};

#endif // POINT_H
