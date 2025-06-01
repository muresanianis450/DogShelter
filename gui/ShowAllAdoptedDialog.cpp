#include "ShowAllAdoptedDialog.h"
#include <QHeaderView>

ShowAllAdoptedDialog::ShowAllAdoptedDialog(const std::vector<Dog>& adoptedDogs, QWidget* parent)
    : QDialog(parent) {
    setWindowTitle("All Adopted Dogs");
    setMinimumSize(600, 400);

    QVBoxLayout* layout = new QVBoxLayout(this);

    tableView = new QTableView(this);
    model = new AdoptedDogsTableModel(this);
    model->setDogs(adoptedDogs);

    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    layout->addWidget(tableView);
}
