#include "analyst.h"
#include "ui_analyst.h"

class Analyst{
    Analyst(QWidget *parent) : QMainWindow(parent){
        ui->setupUi(this);
    }
    ~Analyst(){
        delete ui;
    }

};
