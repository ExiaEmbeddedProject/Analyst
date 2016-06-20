#include "analyst.h"
#include "ui_analyst.h"

Analyst::Analyst(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Analyst)
{
    ui->setupUi(this);
}

Analyst::~Analyst()
{
    delete ui;
}
