#ifndef TOOLS_H
#define TOOLS_H
#include <QProcess.h>
#include <QJsonObject.h>
#include <QFile.h>
#include <QJsonDocument.h>

class tools
{
public:
    static void execCommandLine(QString path, QString parameter);
    static void execCommandLineDetached(QString path, QString parameter);
    static bool writeJsonFile(QString name, QJsonObject object);
};

#endif // TOOLS_H
