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

    this->minor = new Minor();
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
    sbTemperatureMin->setMaximum(350);
    sbTemperatureMin->setValue(260);
    sbTemperatureMin->move(75,50);

    QLabel *lTemperatureMax = new QLabel(this);
    lTemperatureMax->setText("max");
    lTemperatureMax->move(50,85);
    sbTemperatureMax = new QSpinBox(this);
    sbTemperatureMax->setMaximum(350);
    sbTemperatureMax->setValue(320);
    sbTemperatureMax->move(75,85);


    QLabel *lHumidityMin = new QLabel(this);
    lHumidityMin->setText("min");
    lHumidityMin->move(210,50);
    sbHumidityMin = new QSpinBox(this);
    sbHumidityMin->setValue(0);
    sbHumidityMin->move(235,50);
    sbHumidityMin->setMaximum(0);
    sbHumidityMin->setMaximum(100);

    QLabel *lHumidityMax = new QLabel(this);
    lHumidityMax->setText("max");
    lHumidityMax->move(210,85);
    sbHumidityMax = new QSpinBox(this);
    sbHumidityMax->move(235,85);
    sbHumidityMax->setMinimum(0);
    sbHumidityMax->setMaximum(100);
    sbHumidityMax->setValue(100);



    QLabel *lAccelerometerMin = new QLabel(this);
    lAccelerometerMin->setText("min");
    lAccelerometerMin->move(370,50);
    sbAccelerometerMin = new QSpinBox(this);
    sbAccelerometerMin->move(395,50);
    sbAccelerometerMin->setMinimum(-50);
    sbAccelerometerMin->setMaximum(50);
    sbAccelerometerMin->setValue(-10);

    QLabel *lAccelerometerMax = new QLabel(this);
    lAccelerometerMax->setText("max");
    lAccelerometerMax->move(370,85);
    sbAccelerometerMax = new QSpinBox(this);
    sbAccelerometerMax->move(395,85);
    sbAccelerometerMax->setMinimum(-50);
    sbAccelerometerMax->setMaximum(50);
    sbAccelerometerMax->setValue(10);


    QLabel *lGyroscopeMin = new QLabel(this);
    lGyroscopeMin->setText("min");
    lGyroscopeMin->move(520,50);
    sbGyroscopeMin = new QSpinBox(this);
    sbGyroscopeMin->move(545,50);
    sbGyroscopeMin->setMinimum(-50);
    sbGyroscopeMin->setMaximum(50);
    sbGyroscopeMin->setValue(-10);

    QLabel *lGyroscopeMax = new QLabel(this);
    lGyroscopeMax->setText("max");
    lGyroscopeMax->move(520,85);
    sbGyroscopeMax = new QSpinBox(this);
    sbGyroscopeMax->move(545,85);
    sbGyroscopeMax->setMinimum(-50);
    sbGyroscopeMax->setMaximum(50);
    sbGyroscopeMax->setValue(10);


    tableWidget = new QTableWidget(this);
    tableWidget->move(30,140);
    tableWidget->setFixedWidth(942);
    tableWidget->setFixedHeight(440);
    tableWidget->setColumnCount(9);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    tableWidget->setHorizontalHeaderLabels(QStringList() <<"Journey"<<"mTemp"<<"MTemp"<<"mHumidity"<<"MHumidity"<<"mAccelXYZ"<<"MAccelXYZ"<<"mGyroXYZ"<<"MGyroXYZ");

    this->movie = new QMovie("animiners.gif");
    this->movie->setScaledSize(QSize(180,120));
    this->processLabel = new QLabel(this);
    this->processLabel->setMovie(this->movie);
    this->processLabel->move(795,5);
    this->processLabel->setFixedHeight(140);
    this->processLabel->setFixedWidth(200);
    this->movie->start();
    this->processLabel->setVisible(false);
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
    qDebug() << "file: " << tableWidget->selectedItems().first()->text();
    qDebug() << QApplication::applicationDirPath() + "/" + tableWidget->selectedItems().first()->text() + ".json";
    Tools::execCommandLine(filepath, QApplication::applicationDirPath() + "/" + tableWidget->selectedItems().first()->text() + ".json");
}

void Analyst::mine()
{
    this->tableWidget->setRowCount(0);
    QMap<QString, float> sills = QMap<QString, float>();
    sills.insert(QString("tempMin"), sbTemperatureMin->value());
    sills.insert(QString("tempMax"), sbTemperatureMax->value());
    sills.insert(QString("humiMin"), sbHumidityMin->value());
    sills.insert(QString("humiMax"), sbHumidityMax->value());
    sills.insert(QString("accelMin"), sbAccelerometerMin->value());
    sills.insert(QString("accelMax"), sbAccelerometerMax->value());
    sills.insert(QString("gyroMin"), sbGyroscopeMin->value());
    sills.insert(QString("gyroMax"), sbGyroscopeMax->value());

    this->processLabel->setVisible(true);

    this->minor->sills = sills;
    this->minor->table = this->tableWidget;
    this->minor->processLabel = this->processLabel;

    this->minor->start();

    //this->minor.mine(sills, this->tableWidget, this->processLabel);
}
