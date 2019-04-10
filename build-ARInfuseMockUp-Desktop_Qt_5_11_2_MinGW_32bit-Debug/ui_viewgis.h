/********************************************************************************
** Form generated from reading UI file 'viewgis.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWGIS_H
#define UI_VIEWGIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_viewGIS
{
public:

    void setupUi(QDialog *viewGIS)
    {
        if (viewGIS->objectName().isEmpty())
            viewGIS->setObjectName(QStringLiteral("viewGIS"));
        viewGIS->resize(400, 300);

        retranslateUi(viewGIS);

        QMetaObject::connectSlotsByName(viewGIS);
    } // setupUi

    void retranslateUi(QDialog *viewGIS)
    {
        viewGIS->setWindowTitle(QApplication::translate("viewGIS", "2D View - GIS", nullptr));
    } // retranslateUi

};

namespace Ui {
    class viewGIS: public Ui_viewGIS {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWGIS_H
