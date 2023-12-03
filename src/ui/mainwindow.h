#ifndef FINDROUTEAPP_UI_MAINWINDOW_H
#define FINDROUTEAPP_UI_MAINWINDOW_H

#include <QFile>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QSettings>
#include <QString>

#include "../back/Data.h"
#include "../back/EllersAlgorithm.h"
#include "../back/LoadData.h"
#include "../back/Maze.h"
#include "../back/SaveData.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
 public:
  MainWindow(QWidget *parent = nullptr, frp::Data *data = nullptr);
  ~MainWindow();

 private slots:
  void FindRouteButton();
  void OpenFileViaExplorer();
  void QuitFromApp();
  void GenerateMazeButton();
  void SaveButton();

 private:
  Q_OBJECT
  Ui::MainWindow *ui_;
  frp::Data *data_;
  std::queue<int> routes_{};
  QString filepath_{};

  QGraphicsScene *scene_;

  void OpenFile(QString filepath);
  void PlotRoute();
  void PlotMaze();
};
#endif  // FINDROUTEAPP_UI_MAINWINDOW_H
