//
// Created by mures on 5/14/2025.
//

#include "ShowByBreedDialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QPixmap>
#include <QDir>
ShowByBreedDialog::ShowByBreedDialog(Service& service, const QString& whereToSaveFile,QWidget *parent)
    :QDialog(parent) , service(service), currentIndex(0) ,whereToSaveFile(whereToSaveFile) {
    setWindowTitle("Show Dogs by Breed");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    breedInput = new QLineEdit(this);
    searchButton = new QPushButton("Search", this);
    QHBoxLayout* searchLayout = new QHBoxLayout;
    searchLayout->addWidget(new QLabel("Enter Breed:", this));
    searchLayout->addWidget(breedInput);
    searchLayout->addWidget(searchButton);
    mainLayout->addLayout(searchLayout);

    nameLabel = new QLabel(this);
    breedLabel = new QLabel(this);
    ageLabel = new QLabel(this);
    imageLabel = new QLabel(this);
    imageLabel->setFixedSize(300, 300);
    imageLabel->setScaledContents(true);

    mainLayout->addWidget(nameLabel);
    mainLayout->addWidget(breedLabel);
    mainLayout->addWidget(ageLabel);
    mainLayout->addWidget(imageLabel);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    adoptButton = new QPushButton("Adopt");
    nextButton = new QPushButton("Next");
    exitButton = new QPushButton("Exit");

    buttonLayout->addWidget(adoptButton);
    buttonLayout->addWidget(nextButton);
    buttonLayout->addWidget(exitButton);
    mainLayout->addLayout(buttonLayout);

    connect(adoptButton, &QPushButton::clicked, this, &ShowByBreedDialog::onAdoptClicked);
    connect(nextButton, &QPushButton::clicked, this, &ShowByBreedDialog::onNextClicked);
    connect(exitButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(searchButton, &QPushButton::clicked, this, &ShowByBreedDialog::onSearchClicked);


    std::string fileType = whereToSaveFile.toStdString();
    if (fileType == "csv")
        adoptionList = std::make_unique<CSVAdoptionList>();
    else if (fileType == "html")
        adoptionList = std::make_unique<HTMLAdoptionList>();
    else
        adoptionList = nullptr;
}
void ShowByBreedDialog::show_by_breed() {
    QString breed = breedInput->text().trimmed();
    if (breed.isEmpty()) {
        QMessageBox::warning(this, "Invalid input", "Please enter a breed.");
        return;
    }

    dogs = service.getDogsByBreed(breed.toStdString());
    if (!dogs.empty()) {
        displayDog(dogs[currentIndex]);
    } else {
        nameLabel->setText("No dogs available for this breed.");
        breedLabel->clear();
        ageLabel->clear();
        imageLabel->clear();
    }
}


void ShowByBreedDialog::displayDog(const Dog& dog) {
    nameLabel->setText("Name: " + QString::fromStdString(dog.getName()));
    breedLabel->setText("Breed: " + QString::fromStdString(dog.getBreed()));
    ageLabel->setText("Age: " + QString::number(dog.getAge()));
    loadImageFromLocal(QString::fromStdString(dog.getPhotography()));
}

void ShowByBreedDialog::onNextClicked() {
    if (dogs.empty()) return;
    currentIndex = (currentIndex + 1) % dogs.size();
    displayDog(dogs[currentIndex]);
}

void ShowByBreedDialog::onAdoptClicked() {
    if (dogs.empty()) return;

    Dog dog = dogs[currentIndex];
    service.adoptDog(dog);         // Add to adopted list
    service.removeDog(dog);        // Remove from repo

    // Save to file
    if (adoptionList) {
        adoptionList->addDog(dog);
        adoptionList->saveToFile(whereToSaveFile.toStdString() == "csv" ? "adoption_list.csv" : "adoption_list.html");
        QMessageBox::information(this, "Success", "Dog adopted successfully!");
    }

    // Refresh dog list
    dogs = service.getDogsByBreed(breedInput->text().toStdString());

    if (dogs.empty()) {
        nameLabel->setText("No more dogs available.");
        breedLabel->clear();
        ageLabel->clear();
        imageLabel->clear();
        return;
    }

    currentIndex %= dogs.size();
    displayDog(dogs[currentIndex]);
}

void ShowByBreedDialog::loadImageFromLocal(const QString& filePath) {
    // Convert to absolute path if it's relative or not already
    qDebug() << "Loading image from path:" << filePath;
    QString correctedPath = QDir::toNativeSeparators(filePath);
    qDebug() << "Corrected path:" << correctedPath;

    // Load the image into a QPixmap
    QPixmap pixmap;
    if (!pixmap.load(correctedPath)) {
        qDebug() << "Failed to load image:" << correctedPath;
        imageLabel->setText("Image not available");
        imageLabel->setPixmap(QPixmap()); // Clear previous image
        return;
    }

    // Display the loaded image in the label
    imageLabel->setPixmap(pixmap);
}

void ShowByBreedDialog::onSearchClicked() {
    currentIndex = 0;
    show_by_breed();
}