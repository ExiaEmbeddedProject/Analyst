#include "analyst.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Analyst w;
    w.show();

    return a.exec();
}
