//
// Created by mures on 5/11/2025.
//

#include "AddDogDialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include "undoRedo/AddDogCommand.h"

AddDogDialog::AddDogDialog(Service& service,const QString& whereToSaveFile, QWidget *parent)
    : QDialog(parent),whereToSaveFile(whereToSaveFile), service(service) {
    this->setWindowTitle("Add Dog");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout;

    breedInput = new QLineEdit;
    nameInput = new QLineEdit;
    ageInput = new QLineEdit;
    linkInput = new QLineEdit;

    formLayout->addRow("Breed:", breedInput);
    formLayout->addRow("Name:", nameInput);
    formLayout->addRow("Age:", ageInput);
    formLayout->addRow("Photo Link:", linkInput);

    QPushButton *addButton = new QPushButton("Add Dog");
    connect(addButton, &QPushButton::clicked, this, &AddDogDialog::handleAdd);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(addButton);
}

void AddDogDialog::handleAdd(){
    QString breed = breedInput->text();
    QString name = nameInput->text();
    QString ageStr = ageInput->text();
    QString link = linkInput->text();

    bool ok;
    int age = ageStr.toInt(&ok);

    if (!ok || breed.isEmpty() || name.isEmpty() || link.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Please fill in all fields correctly.");
        return;
    }

    Dog d( name.toStdString(),breed.toStdString(), age, link.toStdString());

    try {
        service.addDog(d); // Now calls service which uses command
        QMessageBox::information(this, "Success", "Dog added successfully.");
        this->accept();  // Close the dialog
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }

}