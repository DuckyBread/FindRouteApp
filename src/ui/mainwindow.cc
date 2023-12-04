#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, frp::Data* data)
    : QMainWindow(parent), data_(data)
    , ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    connect(ui_->FindRouteButton, SIGNAL(clicked()), this, SLOT(FindRouteButton()));
    connect(ui_->OpenFileButton, SIGNAL(clicked()), this, SLOT(OpenFileViaExplorer()));
    connect(ui_->actionVia_Explorer, SIGNAL(triggered()), this, SLOT(OpenFileViaExplorer()));
    connect(ui_->actionQuit, SIGNAL(triggered()), this, SLOT(QuitFromApp()));
    connect(ui_->SaveButton, SIGNAL(clicked()), this, SLOT(SaveButton()));
    connect(ui_->GenerateMazeButton, SIGNAL(clicked()), this, SLOT(GenerateMazeButton()));

    scene_ = new QGraphicsScene(QRectF(0,0,500,500), this);
    ui_->graphicsView->setScene(scene_);
    scene_->setBackgroundBrush(Qt::gray);

    ui_->statusbar->showMessage("MAAAAAAAZE", 0);

}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::FindRouteButton()
{
    frp::Maze maze(*data_);

    if (data_->get_cols() == 0 || data_->get_rows() == 0) {
        ui_->statusbar->showMessage("Тут нет лабиринта 🥲");
    } else {
        try {
            maze.FindRoute({ui_->SrcRowSB->value() -1 , ui_->SrcColumnSB->value() -1}, {ui_->DstRowSB->value() - 1, ui_->DstColumnSB->value() - 1});
            ui_->statusbar->showMessage("Нашел путь 🧭");
        } catch (std::exception& e) {
            ui_->statusbar->showMessage(e.what(), 3000);
            return;
        }

        routes_ = maze.get_src_to_dst_route();
        PlotMaze();
        PlotRoute();
    }
}

void MainWindow::OpenFileViaExplorer()
{
    QString filename = QFileDialog::getOpenFileName(this, "Choose file");
    try {
        OpenFile(filename);
    } catch (...) {
        ui_->statusbar->showMessage("Не правильный формат файла!");
        return;
    }

    ui_->DstRowSB->setMaximum(data_->get_rows());
    ui_->DstColumnSB->setMaximum(data_->get_cols());
    ui_->SrcRowSB->setMaximum(data_->get_rows());
    ui_->SrcColumnSB->setMaximum(data_->get_cols());

    PlotMaze();
}

void MainWindow::OpenFile(QString filepath) {
    scene_->clear();

    if (!QFile(filepath).exists()) {
        throw std::logic_error("File cannot be opened");
    }

    frp::LoadData load_data(*data_);
    load_data.ReadFile(filepath.toStdString());

    filepath_ = filepath;
    ui_->statusbar->showMessage("Открыт файл: " + filepath_);
}

void MainWindow::QuitFromApp()
{
    QApplication::quit();
}

void MainWindow::PlotMaze() {
    auto maze_matrixes = data_->get_maze();

    auto x_shift = (float)scene_->width() / data_->get_cols(),
         y_shift = (float)scene_->height() / data_->get_rows();

    scene_->clear();
    scene_->addRect(0,0,500,500,QPen(Qt::red, 2));

    for (auto i = 0; i < maze_matrixes.first.size(); ++i){
        if (maze_matrixes.first[i]) {
            float x0 = x_shift * (i % data_->get_cols() +1),
                  y0 = y_shift * (i / data_->get_rows()),
                  x1 = x0,
                  y1 = y0 + y_shift;
            scene_->addLine(x0,y0,x1,y1, QPen(Qt::red, 2));       }
    }

    for (auto i = 0; i < maze_matrixes.second.size(); ++i){
        if (maze_matrixes.second[i]) {
            float x0 = x_shift * (i % data_->get_cols()),
                  y0 = y_shift * (i / data_->get_rows() +1),
                  x1 = x0 + x_shift,
                  y1 = y0;
            scene_->addLine(x0,y0,x1,y1, QPen(Qt::red, 2));
        }
    }
}

void MainWindow::PlotRoute() {
    auto x_shift = (float)scene_->width() / data_->get_cols(),
         y_shift = (float)scene_->height() / data_->get_rows();
    float x0,y0,x1,y1;

    if (routes_.empty()) {
        ui_->statusbar->showMessage("No way!");
        return;
    }

    while (routes_.size() != 2) {
        int p0 = routes_.front(), p1;
        routes_.pop();
        p1 = routes_.front();

        x0 = x_shift * (p0 % data_->get_cols() + 0.5);
                y0 = y_shift * (p0 / data_->get_rows() + 0.5);
                x1 = x_shift * (p1 % data_->get_cols() + 0.5);
                y1 = y_shift * (p1 / data_->get_rows() + 0.5);
        scene_->addLine(x0, y0, x1, y1, QPen(Qt::green, 2));
    }
    x0 = x_shift * (routes_.front() % data_->get_cols() + 0.5);
    y0 = y_shift * (routes_.front() / data_->get_rows() + 0.5);
    routes_.pop();

    x1 = x_shift * (routes_.front() % data_->get_cols() + 0.5);
    y1 = y_shift * (routes_.front() / data_->get_rows() + 0.5);
    routes_.pop();

    scene_->addLine(x0, y0, x1, y1, QPen(Qt::green, 2));

}

void MainWindow::GenerateMazeButton() {
    data_->set_cols(ui_->GenereRateRowSB->value());
    data_->set_rows(ui_->GenereRateRowSB->value());

    ui_->DstRowSB->setMaximum(data_->get_rows() );
    ui_->DstColumnSB->setMaximum(data_->get_cols());
    ui_->SrcRowSB->setMaximum(data_->get_rows() );
    ui_->SrcColumnSB->setMaximum(data_->get_cols());

    frp::EllersAlgorithm mazeGenerator(*data_);
    data_->set_vertical_matrix(mazeGenerator.get_right_walls());
    data_->set_horizontal_matrix(mazeGenerator.get_bottom_walls());

    ui_->statusbar->showMessage("Сгенерировано 🥳", 3000);

    PlotMaze();
}


void MainWindow::SaveButton(){
    if (data_->get_cols() == 0 || data_->get_rows() == 0) {
        ui_->statusbar->showMessage("Тут нечего сохранять 🥲");
    } else{
        frp::SaveData saver(*data_);
        QString destinationPath = QFileDialog::getSaveFileName(this, "Выбeрите папку", "/", ".txt");
        saver.SaveFile(destinationPath.toStdString());
        ui_->statusbar->showMessage("Сохранено 💾", 3000);
    }
}

