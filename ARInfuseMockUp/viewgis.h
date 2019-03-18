#ifndef VIEWGIS_H
#define VIEWGIS_H

#include <QDialog>

namespace Ui {
class viewGIS;
}

class viewGIS : public QDialog
{
    Q_OBJECT

public:
    explicit viewGIS(QWidget *parent = nullptr);
    ~viewGIS();

private:
    Ui::viewGIS *ui;
};

#endif // VIEWGIS_H
