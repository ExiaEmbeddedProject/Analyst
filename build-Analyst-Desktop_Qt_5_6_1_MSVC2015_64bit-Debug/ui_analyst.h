/********************************************************************************
** Form generated from reading UI file 'analyst.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYST_H
#define UI_ANALYST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Analyst
{
public:
    QWidget *centralWidget;
    QPushButton *commandLineButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QTableWidget *tableWidget;
    QLabel *label;
    QSlider *horizontalSlider;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Analyst)
    {
        if (Analyst->objectName().isEmpty())
            Analyst->setObjectName(QStringLiteral("Analyst"));
        Analyst->resize(652, 433);
        centralWidget = new QWidget(Analyst);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        commandLineButton = new QPushButton(centralWidget);
        commandLineButton->setObjectName(QStringLiteral("commandLineButton"));
        commandLineButton->setGeometry(QRect(550, 20, 75, 23));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(20, 60, 611, 321));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 609, 319));
        tableWidget = new QTableWidget(scrollAreaWidgetContents);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 611, 321));
        scrollArea->setWidget(scrollAreaWidgetContents);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 71, 16));
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(110, 20, 71, 22));
        horizontalSlider->setOrientation(Qt::Horizontal);
        Analyst->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Analyst);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 652, 21));
        Analyst->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Analyst);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Analyst->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Analyst);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Analyst->setStatusBar(statusBar);

        retranslateUi(Analyst);

        QMetaObject::connectSlotsByName(Analyst);
    } // setupUi

    void retranslateUi(QMainWindow *Analyst)
    {
        Analyst->setWindowTitle(QApplication::translate("Analyst", "Analyst", 0));
        commandLineButton->setText(QApplication::translate("Analyst", "DataMining", 0));
        label->setText(QApplication::translate("Analyst", "Temperature:", 0));
    } // retranslateUi

};

namespace Ui {
    class Analyst: public Ui_Analyst {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYST_H
