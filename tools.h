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

class tools : public QObject
{
    Q_OBJECT

public:
    tools(QObject *parent = 0);
    static void execCommandLine(QString path, QString parameter);
    static void execCommandLineDetached(QString path, QString parameter);
    static bool writeJsonFile(QString name, QJsonObject object);
    static QJsonObject createJsonObject(QList<point> path, QList<markedPoint> markedPoints);
    void testdb();
private slots:
    void onDatabasesListed(QStringList);
    void onAllDocumentsRetreived(QVariantList);
    void onDocumentsRetreived(QVariant);
};

#endif // TOOLS_H
