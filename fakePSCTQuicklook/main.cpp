#include "mainwindow.h"
#include <QApplication>
#include "waveformgridwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow sctWindow;
    
    auto waveformGrid = sctWindow.generateWaveformGrid();// Generate the waveform grid layout for SCT

    // Create the custom widget and set it as the central widget of the MainWindow
    WaveformGridWidget* widget = new WaveformGridWidget(waveformGrid);
    sctWindow.setCentralWidget(widget);

    sctWindow.show();
    return a.exec();
}
