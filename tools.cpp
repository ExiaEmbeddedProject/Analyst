#include "tools.h"
#include <QApplication>

void tools::execCommandLine(QString path, QString parameters)
{
    QProcess *process = new QProcess();
    process->start(path, QStringList() << parameters);
}

void tools::execCommandLineDetached(QString path, QString arg)
{
    QStringList args = (QStringList(arg));
    QProcess::startDetached(path, args);
}

bool tools::writeJsonFile(QString path, QJsonObject object)
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

QJsonObject tools::createJsonObject(QList<point> path, QList<markedPoint> markedPoints)
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

QJsonObject getSettings()
{
    QString val;
    QFile file;
    file.setFileName(QApplication::applicationDirPath() + "conf.ini");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject object = d.object();

    return object;
}
