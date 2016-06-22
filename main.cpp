#include "analyst.h"
#include <QApplication>
#include <QSettings>
#include "tools.h"
#include "QProcess"
#include "QDebug"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Analyst w;
    w.show();
    return a.exec();
}
