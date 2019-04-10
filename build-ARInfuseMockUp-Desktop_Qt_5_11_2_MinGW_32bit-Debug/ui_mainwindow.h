/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QGridLayout *gridLayout;
    QPushButton *gisViewBtn;
    QPushButton *viewARBtn;
    QPushButton *settingsBtn;
    QPushButton *exitBtn;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(50, 40, 301, 171));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gisViewBtn = new QPushButton(widget);
        gisViewBtn->setObjectName(QStringLiteral("gisViewBtn"));

        gridLayout->addWidget(gisViewBtn, 0, 0, 1, 1);

        viewARBtn = new QPushButton(widget);
        viewARBtn->setObjectName(QStringLiteral("viewARBtn"));

        gridLayout->addWidget(viewARBtn, 0, 1, 1, 1);

        settingsBtn = new QPushButton(widget);
        settingsBtn->setObjectName(QStringLiteral("settingsBtn"));

        gridLayout->addWidget(settingsBtn, 1, 0, 1, 1);

        exitBtn = new QPushButton(widget);
        exitBtn->setObjectName(QStringLiteral("exitBtn"));

        gridLayout->addWidget(exitBtn, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(exitBtn, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ARINFUSE APP", nullptr));
        gisViewBtn->setText(QApplication::translate("MainWindow", "2D View - GIS", nullptr));
        viewARBtn->setText(QApplication::translate("MainWindow", "3D View - AR/VR", nullptr));
        settingsBtn->setText(QApplication::translate("MainWindow", "Settings", nullptr));
        exitBtn->setText(QApplication::translate("MainWindow", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
