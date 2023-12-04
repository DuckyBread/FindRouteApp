#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  frp::Data data;
  MainWindow w(nullptr, &data);

  w.setFixedSize(w.width(), w.height());
  w.setWindowTitle("FindRouteApp");
  w.show();
  return a.exec();
}
