//
// Created by mures on 5/11/2025.
//

#include "UpdateDogDialog.h"
#pragma once
UpdateDogDialog::UpdateDogDialog(Service& service, QWidget *parent)
    :QDialog(parent), service(service) {

    this->setWindowTitle("Update Dog");
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout;


    //Create input fields
    oldBreedInput = new QLineEdit;
    oldNameInput = new QLineEdit;
    oldAgeInput = new QLineEdit;
    oldLinkInput = new QLineEdit;
    newBreedInput = new QLineEdit;
    newNameInput = new QLineEdit;
    newAgeInput = new QLineEdit;
    newLinkInput = new QLineEdit;
    //Add input fields to the form layout
    formLayout->addRow("Old Breed:", oldBreedInput);
    formLayout->addRow("Old Name:", oldNameInput);
    formLayout->addRow("Old Age:", oldAgeInput);
    formLayout->addRow("Old Photo Link:", oldLinkInput);
    formLayout->addRow("New Breed:", newBreedInput);
    formLayout->addRow("New Name:", newNameInput);
    formLayout->addRow("New Age:", newAgeInput);
    formLayout->addRow("New Photo Link:", newLinkInput);

    QPushButton *updateButton = new QPushButton("Update Dog");
    connect(updateButton, &QPushButton::clicked, this, &UpdateDogDialog::handleUpdate);


    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(updateButton);
}


void UpdateDogDialog::handleUpdate() {

    QString oldBreed = oldBreedInput->text();
    QString oldName = oldNameInput->text();
    QString oldAgeStr = oldAgeInput->text();
    QString oldLink = oldLinkInput->text();
    QString newBreed = newBreedInput->text();
    QString newName = newNameInput->text();
    QString newAgeStr = newAgeInput->text();
    QString newLink = newLinkInput->text();
    bool okOld, okNew;
    int oldAge = oldAgeStr.toInt(&okOld);
    int newAge = newAgeStr.toInt(&okNew);
    // Validate the inputs
    if (!okOld || !okNew || oldBreed.isEmpty() || oldName.isEmpty() || oldLink.isEmpty() ||
        newBreed.isEmpty() || newName.isEmpty() || newLink.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Please fill in all fields correctly.");
        return;
    }
try {
    Dog oldDog( oldName.toStdString(),oldBreed.toStdString(), oldAge, oldLink.toStdString());
    Dog newDog( newName.toStdString(),newBreed.toStdString(), newAge, newLink.toStdString());
    service.updateDog(oldDog, newDog);
    QMessageBox::information(this,"Success","Dog updated successfully.");
    this->accept(); // Close the dialog
}catch (const std::exception& e) {
    QMessageBox::critical(this, "Error", e.what());
}
}