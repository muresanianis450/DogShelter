#include "ChartDialog.h"
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <unordered_map>
#include <algorithm>

ChartDialog::ChartDialog(const std::vector<Dog>& dogs, QWidget* parent)
    : QDialog(parent), view(new QGraphicsView(this)),scene(new QGraphicsScene(this)) {
    adoptedDogs = dogs;
    setWindowTitle("Adopted Dogs Chart");
    setMinimumSize(600, 400);

    view->setScene(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(view);
    setLayout(layout);

    drawChart(dogs);
}

void ChartDialog::drawChart(const std::vector<Dog>& dogs) {
    scene->clear();

    std::unordered_map<std::string, int> breedCount;
    for (const auto& dog : dogs) {
        breedCount[dog.getBreed()]++;
    }

    if (breedCount.empty()) return;

    int maxCount = 0;
    for (const auto& pair : breedCount) {
        maxCount = std::max(maxCount, pair.second);
    }

    QSizeF size = view->viewport()->size();
    int sceneWidth = static_cast<int>(size.width());
    int sceneHeight = static_cast<int>(size.height());

    scene->setSceneRect(0, 0, sceneWidth, sceneHeight);
    scene->setBackgroundBrush(Qt::white);  // White background

    int numBars = static_cast<int>(breedCount.size());
    int spacing = 20;
    int margin = 40;
    int chartHeight = sceneHeight - 2 * margin - 40;
    int chartBottom = sceneHeight - margin;
    int barWidth = std::max(30, (sceneWidth - (spacing * (numBars + 1))) / numBars);

    int x = spacing;
    QFont labelFont("Arial", 10);
    QFont valueFont("Arial", 10, QFont::Bold);

    for (const auto& pair : breedCount) {
        const std::string& breed = pair.first;
        int count = pair.second;

        int barHeight = static_cast<int>((static_cast<double>(count) / maxCount) * chartHeight);
        int barTop = chartBottom - barHeight;

        // Draw bar
        auto* rect = scene->addRect(x, barTop, barWidth, barHeight,
                                    QPen(Qt::black), QBrush(Qt::blue));

        // Draw value label ABOVE the bar
        auto* valueLabel = scene->addText(QString::number(count), valueFont);
        valueLabel->setDefaultTextColor(Qt::black);
        valueLabel->setPos(x + barWidth / 2.0 - valueLabel->boundingRect().width() / 2.0,
                           barTop - valueLabel->boundingRect().height() - 5);

        // Draw breed label BELOW the bar
        auto* label = scene->addText(QString::fromStdString(breed), labelFont);
        label->setDefaultTextColor(Qt::black);
        label->setTextWidth(barWidth);
        label->setPos(x, chartBottom + 5);

        x += barWidth + spacing;
    }

    view->update();
}
void ChartDialog::resizeEvent(QResizeEvent* event) {
    QDialog::resizeEvent(event);
    drawChart(adoptedDogs);
}

void ChartDialog::showEvent(QShowEvent* event) {
    QDialog::showEvent(event);
    drawChart(adoptedDogs); // Ensure the chart is drawn when the dialog is shown
}