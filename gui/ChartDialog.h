#ifndef CHARTDIALOG_H
#define CHARTDIALOG_H

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include "../domain/Dog.h"

class ChartDialog : public QDialog {
    Q_OBJECT

public:
    explicit ChartDialog(const std::vector<Dog>& dogs, QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;
    void showEvent(QShowEvent* event) override;

private:
    void drawChart(const std::vector<Dog>& dogs);
    QGraphicsView* view;
    QGraphicsScene* scene;
    std::vector<Dog> adoptedDogs;
};

#endif // CHARTDIALOG_H
