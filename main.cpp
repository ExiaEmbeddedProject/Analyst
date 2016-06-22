#include "analyst.h"
#include <QApplication>
#include "tools.h"
#include "QProcess"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Analyst w;
    w.show();

    return a.exec();
}
