#ifndef FINDROUTEAPP_UI_MAZEPLOTING_H
#define FINDROUTEAPP_UI_MAZEPLOTING_H

#include <QMainWindow>
#include <QOpenGLWidget>
#include <QtOpenGL>

class MazePlotting : public QOpenGLWidget {
 public:
  MazePlotting(QWidget *parrent = nullptr);
  ~MazePlotting();

 private:
  Q_OBJECT;
  void initializeGL() override;
  void paintGL() override;
};

#endif  // FINDROUTEAPP_UI_MAZEPLOTING_H
