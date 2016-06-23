#include "tools.h"
#include <QApplication>
#include "couchdb.h"
#include <QSettings>

Tools::Tools(QObject* parent) : QObject(parent)
{}

void Tools::execCommandLine(QString path, QString parameters)
{
    QProcess *process = new QProcess();
    process->start(path, QStringList() << parameters);
}

void Tools::execCommandLineDetached(QString path, QString arg)
{
    QStringList args = (QStringList(arg));
    QProcess::startDetached(path, args);
}

bool Tools::writeJsonFile(QString path, QJsonObject object)
{
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open file.");
        return false;
    }

    QJsonDocument document(object);

    file.write(document.toJson());

    return true;
}

QJsonObject Tools::createJsonObject(QList<point> path, QList<markedPoint> markedPoints)
{
    QJsonObject object;

    QJsonArray array;
    array = QJsonArray();
    foreach(point element, path)
    {
        QJsonObject obj;
        element.write(obj);
        array.append(obj);
    }
    object["path"] = array;

    array = QJsonArray();
    foreach(markedPoint element, markedPoints)
    {
        QJsonObject obj;
        element.write(obj);
        array.append(obj);
    }
    object["markedPoints"] = array;

    return object;
}
