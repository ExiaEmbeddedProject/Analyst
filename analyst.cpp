#include "analyst.h"
#include "ui_analyst.h"
#include "tools.h"

Analyst::Analyst(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Analyst)
{
    ui->setupUi(this);

    QPushButton *m_bouton = new QPushButton("Test", this);
    m_bouton->move(200, 25);

    QObject::connect(
                m_bouton,
                SIGNAL(clicked()),
                this,
                SLOT(
                    callTracker()
                )
    );
}

Analyst::~Analyst()
{
    delete ui;
}

void Analyst::callTracker()
{
    tools::execCommandLineDetached("D:/Work/pri/Js/Tracker/dist/win-unpacked/tracker.exe", "D:/Work/pri/Js/Tracker/samples/dataSet.Json");
}