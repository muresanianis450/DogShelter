#ifndef SHOWONEBYONEDIALOG_H
#define SHOWONEBYONEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "../service/service.h"
#include "../adoption/AdoptionListFactory.h"
#include <memory>

class ShowOneByOneDialog : public QDialog {
  Q_OBJECT

public:
  explicit ShowOneByOneDialog(Service& service, const QString& whereToSaveFile,QWidget *parent = nullptr);

  private slots:
  void onNextClicked();
  void onAdoptClicked();

  void loadImageFromLocal(const QString &filePath);

private:
  void show_one_by_one();
  void displayDog(const Dog& dog);
 void loadImageFromUrl(const QString &url);
  QString whereToSaveFile;

  Service& service;
  std::vector<Dog> dogs;
  int currentIndex;
  std::unique_ptr<AdoptionList> adoptionList;

  QLabel* nameLabel;
  QLabel* breedLabel;
  QLabel* ageLabel;
  QLabel* imageLabel;
  QPushButton* adoptButton;
  QPushButton* nextButton;
  QPushButton* exitButton;

};

#endif // SHOWONEBYONEDIALOG_H