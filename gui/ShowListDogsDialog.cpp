#include "ShowListDogsDialog.h"
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>

ShowListDogsDialog::ShowListDogsDialog(Service& service, QWidget *parent)
    : QDialog(parent), service(service) {
    this->setWindowTitle("Dog List");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Create the table widget
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(4); // Breed, Name, Age, Link
    tableWidget->setHorizontalHeaderLabels({"Breed", "Name", "Age", "Link"});
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Set a minimum size for the table
    tableWidget->setMinimumSize(600, 400); // Minimum Width: 600px, Minimum Height: 400px


    // Add the table to the layout
    mainLayout->addWidget(tableWidget);

    // Populate the table with data
    populateTable();
}

void ShowListDogsDialog::populateTable() {
    const auto& dogs = service.getAllDogs();
    tableWidget->setRowCount(dogs.size());

    for (int row = 0; row < dogs.size(); row++) {
        const Dog& dog = dogs[row];
        tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(dog.getBreed())));
        tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(dog.getName())));
        tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(dog.getAge())));
        tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(dog.getPhotography())));
    }
}