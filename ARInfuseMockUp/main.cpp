#include "mainwindow.h"
#include <QApplication>

namespace {

const char* kDefaultToolPath = "C:/Users/arteam/Documents/arinfuse";
const char* kDefaultDataPath =  "C:/Users/arteam/Documents/arinfuse/Cyprus_data";

}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w(kDefaultToolPath, kDefaultDataPath);
  w.show();

  return a.exec();
}
