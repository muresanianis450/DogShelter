// MainWindow.cpp

#include "MainWindow.h"
#include "AddDogDialog.h"
#include "RemoveDogDialog.h"
#include "UpdateDogDialog.h"
#include "ShowListDogsDialog.h"
#include "ShowOneByOneDialog.h"
#include "ShowByBreedDialog.h"
#include "ShowAllAdoptedDialog.h"
#include "ChartDialog.h"
#include <QMessageBox>
#include <QKeySequence>
#include "../gui/AdoptedDogsTableModel.h"

MainWindow::MainWindow(Service& service, QWidget *parent)
    : QMainWindow(parent), service(service), stackedWidget(new QStackedWidget(this)) {

    // Initialize Undo/Redo buttons before adding to layout
    undoButton = new QPushButton("Undo");
    redoButton = new QPushButton("Redo");

    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    // Layout for undo/redo
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(undoButton);
    buttonLayout->addWidget(redoButton);

    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(stackedWidget);

    central->setLayout(mainLayout);
    setCentralWidget(central);

    connect(undoButton, &QPushButton::clicked, this, &MainWindow::undoLastOperation);
    connect(redoButton, &QPushButton::clicked, this, &MainWindow::redoLastOperation);

    setupShortcuts();

    stackedWidget->addWidget(createStartPage());
    stackedWidget->addWidget(createModePage());
    stackedWidget->addWidget(createAdminPage());
    stackedWidget->addWidget(createUserPage());
    stackedWidget->setCurrentIndex(0); // Show start page first
}

void MainWindow::setupShortcuts() {
    // Use operator| instead of deprecated operator+
    undoShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z), this);
    redoShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y), this);

    connect(undoShortcut, &QShortcut::activated, this, &MainWindow::undoLastOperation);
    connect(redoShortcut, &QShortcut::activated, this, &MainWindow::redoLastOperation);
}

QWidget* MainWindow::createStartPage() {
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    QPushButton *csvButton = new QPushButton("CSV");
    QPushButton *htmlButton = new QPushButton("HTML");

    layout->addWidget(csvButton);
    layout->addWidget(htmlButton);

    connect(csvButton, &QPushButton::clicked, this, [this]() {
        this->whereToSaveFile = "csv";
        goToModePage();
    });
    connect(htmlButton, &QPushButton::clicked, this, [this]() {
        this->whereToSaveFile = "html";
        goToModePage();
    });

    return page;
}

QWidget* MainWindow::createModePage() {
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    QPushButton *adminButton = new QPushButton("Admin Mode");
    QPushButton *userButton = new QPushButton("User Mode");
    connect(adminButton, &QPushButton::clicked, this, &MainWindow::goToAdminPage);
    connect(userButton, &QPushButton::clicked, this, &MainWindow::goToUserPage);

    layout->addWidget(adminButton);
    layout->addWidget(userButton);

    QPushButton* showChartButton = new QPushButton("Show Chart");
    layout->addWidget(showChartButton);
    connect(showChartButton, &QPushButton::clicked, this, [this]() {
        try {
            std::string type = whereToSaveFile;
            std::transform(type.begin(), type.end(), type.begin(), ::toupper);

            auto adoptionList = AdoptionListFactory::createAdoptionList(type);
            auto dogs = adoptionList->getAdoptedDogs();
            ChartDialog dialog(dogs, this);
            dialog.exec();
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    });
    return page;
}

QWidget* MainWindow::createAdminPage() {
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    this->setWindowTitle("Admin Mode");
    QPushButton *addButton = new QPushButton("ADD DOG");
    QPushButton *removeButton = new QPushButton("REMOVE DOG");
    QPushButton *updateButton = new QPushButton("UPDATE DOG");
    QPushButton *printButton = new QPushButton("PRINT ALL DOGS");

    layout->addWidget(addButton);
    layout->addWidget(removeButton);
    layout->addWidget(updateButton);
    layout->addWidget(printButton);

    connect(addButton, &QPushButton::clicked, this, [this]() {
        AddDogDialog dialog(this->service, QString::fromStdString(this->whereToSaveFile), this);
        dialog.exec();
    });
    connect(removeButton, &QPushButton::clicked, this, [this]() {
        RemoveDogDialog dialog(this->service, this);
        dialog.exec();
    });
    connect(updateButton, &QPushButton::clicked, this, [this]() {
        UpdateDogDialog dialog(this->service, this);
        dialog.exec();
    });
    connect(printButton, &QPushButton::clicked, this, [this]() {
        ShowListDogsDialog dialog(this->service, this);
        dialog.exec();
    });

    return page;
}

void MainWindow::onShowAdoptedDogsClicked() {
    ShowAllAdoptedDialog* dialog = new ShowAllAdoptedDialog(service.getAdoptedDogs(), this);
    dialog->exec();
}

void MainWindow::goToUserPage() {
    stackedWidget->setCurrentIndex(3); // User Page index
    // No more undoRedoDialog
}

void MainWindow::goToModePage() const {
    stackedWidget->setCurrentIndex(1); // Mode Page Index
    // No more undoRedoDialog
}

void MainWindow::goToAdminPage() {
    stackedWidget->setCurrentIndex(2); // Admin Page index
    // No more undoRedoDialog
}

QWidget *MainWindow::createUserPage() {
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    this->setWindowTitle("User Mode");

    QPushButton *showDogsButton = new QPushButton("Show Dogs");
    QPushButton *showByBreedButton = new QPushButton("Show by Breed");
    QPushButton *printCurrentButton = new QPushButton("Print Current Adopted Dogs");
    QPushButton *printAdoptionButton = new QPushButton("Print Adoption List");

    layout->addWidget(showDogsButton);
    layout->addWidget(showByBreedButton);
    layout->addWidget(printCurrentButton);
    layout->addWidget(printAdoptionButton);

    connect(showDogsButton, &QPushButton::clicked, this, [this]() {
        ShowOneByOneDialog dialog(this->service, QString::fromStdString(this->whereToSaveFile), this);
        dialog.exec();
    });
    connect(showByBreedButton, &QPushButton::clicked, this, [this]() {
        ShowByBreedDialog dialog(this->service, QString::fromStdString(this->whereToSaveFile), this);
        dialog.exec();
    });
    connect(printCurrentButton, &QPushButton::clicked, this, [this]() {
        ShowAllAdoptedDialog dialog(service.getAdoptedDogs(), this);
        dialog.exec();
    });
    connect(printAdoptionButton, &QPushButton::clicked, this, [this]() {
        try {
            std::string type = whereToSaveFile;
            std::transform(type.begin(), type.end(), type.begin(), ::toupper);

            auto adoptionList = AdoptionListFactory::createAdoptionList(type);
            auto dogs = adoptionList->getAdoptedDogs();

            ShowAllAdoptedDialog dialog(dogs, this);
            dialog.exec();
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    });
    return page;
}

void MainWindow::undoLastOperation() {
    if (service.undo()) {
        QMessageBox::information(this, "Undo", "Last operation undone");
    }
}

void MainWindow::redoLastOperation() {
    if (service.redo()) {
        QMessageBox::information(this, "Redo", "Last operation redone");
    }
}