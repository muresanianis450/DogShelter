//
// Created by mures on 5/14/2025.
//

#ifndef SHOWBYBREEDDIALOG_H
#define SHOWBYBREEDDIALOG_H

#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include "service/service.h"
#include "adoption/AdoptionListFactory.h"
#include <memory>

class ShowByBreedDialog : public QDialog {
  Q_OBJECT

public:
  ShowByBreedDialog(Service& service, const QString& whereToSaveFile,QWidget *parent = nullptr);

  private slots:
      void onNextClicked();
  void onAdoptClicked();
  void onSearchClicked();
  void loadImageFromLocal(const QString &filePath);

private:
  void show_by_breed();
  void displayDog(const Dog& dog);
  QString whereToSaveFile;

  std::unique_ptr<AdoptionList> adoptionList;
  Service& service;
  std::vector<Dog> dogs;
  int currentIndex;

  QLineEdit* breedInput;
  QLabel* nameLabel;
  QLabel* breedLabel;
  QLabel* ageLabel;
  QLabel* imageLabel;
  QPushButton* adoptButton;
  QPushButton* nextButton;
  QPushButton* exitButton;
  QPushButton* searchButton;
};

#endif // SHOWBYBREEDDIALOG_H
