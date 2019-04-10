/********************************************************************************
** Form generated from reading UI file 'viewarvr.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWARVR_H
#define UI_VIEWARVR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ViewARVR
{
public:
    QLabel *label_pic;
    QPushButton *showImage;

    void setupUi(QDialog *ViewARVR)
    {
        if (ViewARVR->objectName().isEmpty())
            ViewARVR->setObjectName(QStringLiteral("ViewARVR"));
        ViewARVR->resize(567, 458);
        label_pic = new QLabel(ViewARVR);
        label_pic->setObjectName(QStringLiteral("label_pic"));
        label_pic->setGeometry(QRect(220, 60, 311, 291));
        showImage = new QPushButton(ViewARVR);
        showImage->setObjectName(QStringLiteral("showImage"));
        showImage->setGeometry(QRect(40, 90, 101, 41));

        retranslateUi(ViewARVR);

        QMetaObject::connectSlotsByName(ViewARVR);
    } // setupUi

    void retranslateUi(QDialog *ViewARVR)
    {
        ViewARVR->setWindowTitle(QApplication::translate("ViewARVR", "3D View - AR/VR", nullptr));
        label_pic->setText(QString());
        showImage->setText(QApplication::translate("ViewARVR", "AR view", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ViewARVR: public Ui_ViewARVR {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWARVR_H
