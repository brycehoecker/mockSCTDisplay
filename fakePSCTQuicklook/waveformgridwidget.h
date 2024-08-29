#ifndef WAVEFORMGRIDWIDGET_H
#define WAVEFORMGRIDWIDGET_H
#include <QWidget>
#include <QVector>
#include <QResizeEvent>
#include <QPaintEvent>
#include <vector>

class WaveformGridWidget : public QWidget{
	Q_OBJECT
	public:
		explicit WaveformGridWidget(QWidget *parent = nullptr);
		explicit WaveformGridWidget(std::vector<std::vector<std::vector<double>>>& waveforms, QWidget *parent = nullptr);
		static double generateWaveform(int t);// Function to generate waveform for a pixel

	protected:
		void resizeEvent(QResizeEvent *event) override;
		void paintEvent(QPaintEvent *event) override;

	private:
		std::vector<std::vector<std::vector<double>>> m_waveforms;  // Updated to match the waveform data type
		// Function to resize the grid of waveforms to fit the widget
		void resizeWaveforms(int width, int height);
		int m_gridSize;
};//class WaveformGridWidget
#endif // WAVEFORMGRIDWIDGET_H
