#include "analyst.h"
#include <QApplication>
#include <QSettings>
#include "tools.h"
#include "QProcess"
#include "QDebug"
#include "couchdb.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings settings("conf.ini", QSettings::IniFormat);
    QString url = settings.value("database/url").toString();
    QString dbname = settings.value("database/name").toString();

    qDebug() << "Couchdb url: " << url;
    qDebug() << "Couchdb database: " << dbname;

    Couchdb db;
    db.getAllDocuments(url, dbname);

    Analyst w;
    w.show();
    return a.exec();
}
