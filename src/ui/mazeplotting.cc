#include "mazeplotting.h"

MazePlotting::MazePlotting(QWidget* parrent): QOpenGLWidget(parrent) {}

MazePlotting::~MazePlotting() {}

void MazePlotting::initializeGL() {
    glClear(GL_COLOR_BUFFER_BIT);

}

void MazePlotting::paintGL() {

}
