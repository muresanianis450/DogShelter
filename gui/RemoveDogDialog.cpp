//
// Created by mures on 5/11/2025.
//

#include "RemoveDogDialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

RemoveDogDialog::RemoveDogDialog(Service& service, QWidget *parent)
    :QDialog(parent),service(service) {


    this->setWindowTitle("Remove Dog");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout;


    //Create input fields
    breedInput = new QLineEdit;
    nameInput = new QLineEdit;
    ageInput = new QLineEdit;
    linkInput = new QLineEdit;

    //Add input fields to the form layout
    formLayout->addRow("Breed:", breedInput);
    formLayout->addRow("Name:", nameInput);
    formLayout->addRow("Age:", ageInput);
    formLayout->addRow("Photo Link:", linkInput);

    //Create the remove button
    QPushButton *removeButton = new QPushButton("Remove Dog");
    // Connect the button's clicked signal to the handleRemove slot
    connect(removeButton, &QPushButton::clicked, this, &RemoveDogDialog::handleRemove);


    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(removeButton);

}

void RemoveDogDialog::handleRemove() {
    // Get the input values
    QString breed = breedInput->text();
    QString name = nameInput->text();
    QString ageStr = ageInput->text();
    QString link = linkInput->text();
    bool ok;
    int age = ageStr.toInt(&ok);
    // Validate the inputs
    if (!ok || breed.isEmpty() || name.isEmpty() || link.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Please fill in all fields correctly.");
        return;
    }
    Dog d( name.toStdString(),breed.toStdString(), age, link.toStdString());
    try {
        service.removeDog(d);
        QMessageBox::information(this,"Success","Dog removed successfully.");
        this->accept(); //Close the dialo
    }catch (const std::exception& e) {
        QMessageBox::critical(this,"Error",e.what());
    }
}