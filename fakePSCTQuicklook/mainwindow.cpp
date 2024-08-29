#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cstdlib>  // for rand()
#include <ctime>  // for time()

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

std::vector<double> MainWindow::generateRandomWaveform() {
    std::vector<double> waveform(64);  // or 128, according to your requirements
    srand(time(0));  // initialize random seed

    for(auto & value : waveform) {
        value = static_cast<double>(rand()) / RAND_MAX;  // generate a random value between 0.0 and 1.0
    }
    return waveform;
}// generateRandomWaveform

std::vector<std::vector<std::vector<double>>> MainWindow::generateWaveformGrid() {
    int grid_width = 120;  // width of the grid
    int grid_height = 120;  // height of the grid
    std::vector<std::vector<std::vector<double>>> grid(grid_height, std::vector<std::vector<double>>(grid_width));

    for(auto & row : grid) {
        for(auto & column : row) {
            column = generateRandomWaveform();  // assign each pixel a random waveform
        }// for(auto & column : row)
    }// for(auto & row : grid)
    return grid;
}// generateWaveformGrid
