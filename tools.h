#ifndef TOOLS_H
#define TOOLS_H
#include <QProcess.h>
#include <QJsonObject.h>
#include <QFile.h>
#include <QJsonDocument.h>
#include <point.h>
#include <markedpoint.h>
#include <QJsonArray.h>
#include <QVariant>
#include <QVariantList>
#include <QObject>

class Tools : public QObject
{
    Q_OBJECT

public:
    Tools(QObject *parent = 0);
    static void execCommandLine(QString path, QString parameter); // TODO: use namespace instead of a class for static functions
    static void execCommandLineDetached(QString path, QString parameter);
    static bool writeJsonFile(QString name, QJsonObject object);
    static QJsonObject createJsonObject(QList<point> path, QList<markedPoint> markedPoints);
};

#endif // TOOLS_H
