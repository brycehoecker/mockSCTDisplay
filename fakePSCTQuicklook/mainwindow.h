#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <vector>  // Include the vector library

//Not really sure why this works here
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        // Add the declaration of the waveform generator function
        std::vector<double> generateRandomWaveform();
        std::vector<std::vector<std::vector<double>>> generateWaveformGrid();

    private:
        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
