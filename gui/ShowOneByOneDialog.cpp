#include "ShowOneByOneDialog.h"
#include <QPixmap>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
ShowOneByOneDialog::ShowOneByOneDialog(Service& service, const QString& whereToSaveFile,QWidget *parent)
    : QDialog(parent), service(service), currentIndex(0) , whereToSaveFile(whereToSaveFile){

    // Validate file type before creating adoption list
    if (whereToSaveFile != "csv" && whereToSaveFile != "html") {
        QMessageBox::warning(this, "Error", "Invalid file type specified");

    }
    setWindowTitle("Show Dogs One by One");
    resize(400, 500);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
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

    connect(adoptButton, &QPushButton::clicked, this, &ShowOneByOneDialog::onAdoptClicked);
    connect(nextButton, &QPushButton::clicked, this, &ShowOneByOneDialog::onNextClicked);
    connect(exitButton, &QPushButton::clicked, this, &QDialog::accept);

    std::string fileType = whereToSaveFile.toStdString();
    if (fileType == "csv")
        adoptionList = std::make_unique<CSVAdoptionList>();
    else if (fileType == "html")
        adoptionList = std::make_unique<HTMLAdoptionList>();
    else
        adoptionList = nullptr;

    show_one_by_one();
}

void ShowOneByOneDialog::show_one_by_one() {
    dogs = service.getAllDogs();
    if (!dogs.empty()) {
        currentIndex = 0; // Reset index
        displayDog(dogs[currentIndex]);
    } else {
        nameLabel->setText("No dogs available.");
        breedLabel->clear();
        ageLabel->clear();
        imageLabel->clear();
        // Disable buttons when no dogs
        adoptButton->setEnabled(false);
        nextButton->setEnabled(false);
    }
}

void ShowOneByOneDialog::displayDog(const Dog& dog) {
    nameLabel->setText("Name: " + QString::fromStdString(dog.getName()));
    breedLabel->setText("Breed: " + QString::fromStdString(dog.getBreed()));
    ageLabel->setText("Age: " + QString::number(dog.getAge()));
    loadImageFromLocal(QString::fromStdString(dog.getPhotography()));
}

void ShowOneByOneDialog::onNextClicked() {
        if (dogs.empty()) {
            QMessageBox::information(this, "Info", "No dogs available");
            return;
        }
    currentIndex = (currentIndex + 1) % dogs.size();
    displayDog(dogs[currentIndex]);
}


void ShowOneByOneDialog::onAdoptClicked() {
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
    dogs = service.getAllDogs();

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

void ShowOneByOneDialog::loadImageFromLocal(const QString& filePath) {
    imageLabel->clear(); // Clear previous image

    if (filePath.isEmpty()) {
        imageLabel->setText("No image available");
        return;
    }

    QPixmap pixmap;
    if (!pixmap.load(filePath)) {
        // Try with different path formats if needed
        QString localPath = QDir::currentPath() + "/" + filePath;
        if (!pixmap.load(localPath)) {
            imageLabel->setText("Image not found");
            return;
        }
    }

    imageLabel->setPixmap(pixmap.scaled(imageLabel->size(),
        Qt::KeepAspectRatio, Qt::SmoothTransformation));
}