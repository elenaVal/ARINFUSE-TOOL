#ifndef VIEWARVR_H
#define VIEWARVR_H

#include <QDialog>

namespace Ui {
class ViewARVR;
}

class ViewARVR : public QDialog
{
    Q_OBJECT

public:
    explicit ViewARVR(QWidget *parent = nullptr);
    ~ViewARVR();

    void showARImage();
    void runLARAapp();
    void showNormalImage();

private slots:
    void on_showImage_clicked();

private:
    Ui::ViewARVR *ui;
};

#endif // VIEWARVR_H
