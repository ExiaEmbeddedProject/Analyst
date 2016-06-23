#include "analyst.h"
#include "ui_analyst.h"
#include "tools.h"
#include "QScrollArea.h"
#include "QTableWidget.h"
#include "QPushButton.h"
#include "QDebug.h"
#include "QLabel.h"
#include "QSpinBox.h"
#include <QSettings>

Analyst::Analyst(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Analyst)
{
    ui->setupUi(this);

    this->draw();
    this->bind();

    this->minor = Minor();
}

Analyst::~Analyst()
{
    delete ui;
}

void Analyst::draw()
{
    setFixedSize(1000, 600);
    statusBar()->setSizeGripEnabled(false);


    QLabel *lTemperature = new QLabel(this);
    lTemperature->setText("Temperature");
    lTemperature->move(50,20);

    QLabel *lHumidity = new QLabel(this);
    lHumidity->setText("Humidity");
    lHumidity->move(210,20);

    QLabel *lAccel = new QLabel(this);
    lAccel->setText("Accelerometer");
    lAccel->move(370,20);

    QLabel *lGyro = new QLabel(this);
    lGyro->setText("Gyroscope");
    lGyro->move(520,20);

    bDataMining = new QPushButton("DataMining", this);
    bDataMining->move(680, 67);

    lToolTip = new QLabel(this);
    lToolTip->setVisible(false);
    lToolTip->setText("Calculating...");
    lToolTip->move(800,67);

    QLabel *lTemperatureMin = new QLabel(this);
    lTemperatureMin->setText("min");
    lTemperatureMin->move(50,50);
    sbTemperatureMin = new QSpinBox(this);
    sbTemperatureMin->setValue(0);
    sbTemperatureMin->move(75,50);

    QLabel *lTemperatureMax = new QLabel(this);
    lTemperatureMax->setText("max");
    lTemperatureMax->move(50,85);
    sbTemperatureMax = new QSpinBox(this);
    sbTemperatureMax->setValue(300);
    sbTemperatureMax->move(75,85);


    QLabel *lHumidityMin = new QLabel(this);
    lHumidityMin->setText("min");
    lHumidityMin->move(210,50);
    sbHumidityMin = new QSpinBox(this);
    sbHumidityMin->setValue(0);
    sbHumidityMin->move(235,50);

    QLabel *lHumidityMax = new QLabel(this);
    lHumidityMax->setText("max");
    lHumidityMax->move(210,85);
    sbHumidityMax = new QSpinBox(this);
    sbHumidityMax->setValue(300);
    sbHumidityMax->move(235,85);



    QLabel *lAccelerometerMin = new QLabel(this);
    lAccelerometerMin->setText("min");
    lAccelerometerMin->move(370,50);
    sbAccelerometerMin = new QSpinBox(this);
    sbAccelerometerMin->setValue(0);
    sbAccelerometerMin->move(395,50);

    QLabel *lAccelerometerMax = new QLabel(this);
    lAccelerometerMax->setText("max");
    lAccelerometerMax->move(370,85);
    sbAccelerometerMax = new QSpinBox(this);
    sbAccelerometerMax->setValue(300);
    sbAccelerometerMax->move(395,85);


    QLabel *lGyroscopeMin = new QLabel(this);
    lGyroscopeMin->setText("min");
    lGyroscopeMin->move(520,50);
    sbGyroscopeMin = new QSpinBox(this);
    sbGyroscopeMin->setValue(0);
    sbGyroscopeMin->move(545,50);

    QLabel *lGyroscopeMax = new QLabel(this);
    lGyroscopeMax->setText("max");
    lGyroscopeMax->move(520,85);
    sbGyroscopeMax = new QSpinBox(this);
    sbGyroscopeMax->setValue(300);
    sbGyroscopeMax->move(545,85);


    tableWidget = new QTableWidget(this);
    tableWidget->move(30,140);
    tableWidget->setFixedWidth(942);
    tableWidget->setFixedHeight(440);
    tableWidget->setColumnCount(9);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    tableWidget->setHorizontalHeaderLabels(QStringList() <<"Journey"<<"mTemp"<<"MTemp"<<"mHumidity"<<"MHumidity"<<"mAccelXYZ"<<"MAccelXYZ"<<"mGyroXYZ"<<"MGyroXYZ");
}

void Analyst::bind()
{
    QObject::connect(
        tableWidget,
        SIGNAL(doubleClicked(QModelIndex)),
        this,
        SLOT(
            callTracker()
        )
    );

    QObject::connect(
        bDataMining,
        SIGNAL(clicked(bool)),
        this,
        SLOT(mine())
    );
}

void Analyst::callTracker()
{
    QSettings settings("conf.ini", QSettings::IniFormat);
    QString filepath = settings.value("external/tracker").toString();
    qDebug() << "Tracker path: " << filepath;
    Tools::execCommandLineDetached(filepath, QApplication::applicationDirPath() + "/" + tableWidget->selectedItems().first()->text() + ".json");
}

void Analyst::mine()
{
    QMap<QString, float> sills = QMap<QString, float>();
    sills.insert(QString("tagada"), 2);

    this->minor.doJob(sills, this->tableWidget);
    lToolTip->setVisible("true");

}
