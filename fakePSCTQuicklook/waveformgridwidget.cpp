#include "waveformgridwidget.h"
#include <QPainter>
#include <cmath>
#include <set>

WaveformGridWidget::WaveformGridWidget(QWidget *parent) : QWidget(parent), m_gridSize{120}{
    setMinimumSize(m_gridSize * 2, m_gridSize * 2);
    resizeWaveforms(width(), height());
}

WaveformGridWidget::WaveformGridWidget(std::vector<std::vector<std::vector<double>>>& waveforms, QWidget *parent)
														: QWidget(parent), m_waveforms(waveforms), m_gridSize{120}{
    setMinimumSize(m_gridSize * 2, m_gridSize * 2);
    resizeWaveforms(width(), height());
}//

double WaveformGridWidget::generateWaveform(int t){
    return 0.5 * (1 + std::sin(2 * M_PI * t / 128.0));
}//generateWaveform

void WaveformGridWidget::resizeEvent(QResizeEvent *event){
    resizeWaveforms(event->size().width(), event->size().height());
    QWidget::resizeEvent(event);
}//resizeEvent

void WaveformGridWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    int minBlockSize = 2; // Minimum size for the blocks
    int blockSize = std::max(minBlockSize, std::min(width(), height()) / m_gridSize); //Making sure the window always includes the waveform pxiels
    int innerBlockSize = std::max(1, blockSize - 2); // Ensure that innerBlockSize is at least 1
    QColor spaceColor(0, 0, 0); // black color for spaces in between "pixels"

    // Calculate the offsets to center the grid within the widget
    int xOffset = (width() - (blockSize * m_gridSize)) / 2;
    int yOffset = (height() - (blockSize * m_gridSize)) / 2;

    // Clear the widget with the spacing color
    painter.fillRect(0, 0, width(), height(), spaceColor);

    // The number (and location) of th 8x8 pixel grids (Front-End Module) removed from the corners of the 120x120 "Square Display Grid"
    const std::array<int, 48> corners = {
        0, 1, 2, 3, 4, 15, 30, 45, 60, 16, 17, 31, 10, 11, 12, 13, 14, 29, 44, 59, 74, 27, 28, 43,
        150, 165, 180, 195, 210, 211, 212, 213, 214, 181, 196, 197, 220, 221, 222, 223, 224, 209, 194, 179, 164, 207, 208, 193
    };

    for (int i = 0; i < m_gridSize; i++) {
        for (int j = 0; j < m_gridSize; j++) {
            int blockIndex = i / 8 + 15 * (j / 8); // Calculate the 8x8 block index          
            /// TODO: This might be generating the black pixels still but just ignoring/skipping them
            /// It would probably be more efficient to come up with a way to never generate them in the first place
            // Check if the current block index is one of the corners
            if (std::find(std::begin(corners), std::end(corners), blockIndex) != std::end(corners)) {
                continue; // Skip the corner blocks
            }
            // Use the first value in the inner vector for color. Adjust as needed.
            double waveformValue = m_waveforms[i][j][0];
            // Map the waveform value to a hue (assuming the value is in [0, 1])
            int hue = static_cast<int>(waveformValue * 359);
            QColor color = QColor::fromHsv(hue, 255, 255);
            
            /// TODO: These "Black Borders" are actually still filled in pixels.
            /// Would be more efficient and faster to find a way to just add gap without filling a pixle with black color
            int x = xOffset + i * blockSize + 1; // '+ 1' ensures a black border on the left side of the block
            int y = yOffset + j * blockSize + 1; // '+ 1' ensures a black border on the top side of the block

            painter.fillRect(x, y, innerBlockSize, innerBlockSize, color);
        }//for int j
    }//for int i
}//paintEvent

void WaveformGridWidget::resizeWaveforms(int width, int height){
    m_waveforms.resize(width);
    for (int i = 0; i < width; i++) {
        m_waveforms[i].resize(height);
        for (int j = 0; j < height; j++) {
            m_waveforms[i][j] = {generateWaveform(i + j)}; // Adjust as needed. This currently creates a vector with a single value.
        }//for int j
    }//for int i
}//resizeWaveforms
