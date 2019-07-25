#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "viewarvr.h"
#include "viewgis.h"
#include "settings.h"
#include<QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_viewARBtn_clicked();

    void on_gisViewBtn_clicked();

    void on_settingsBtn_clicked();

private:
    Ui::MainWindow *ui;
    ViewARVR *viewARVR;
    viewGIS *viewgis;
    Settings *settings;

public:
    QProcess *gisProcess;
     void ReadOut();

};

#endif // MAINWINDOW_H
