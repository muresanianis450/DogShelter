//
// Created by mures on 5/11/2025.
//
#pragma once
#ifndef ADDDOGDIALOG_H
#define ADDDOGDIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include "service/service.h"

class AddDogDialog : public QDialog {
    Q_OBJECT

public:
      AddDogDialog(Service& service, const QString& whereToSaveFile,QWidget *parent = nullptr);

private slots: //
        void handleAdd();

private:
  Service& service;
    QString whereToSaveFile;
   QLineEdit *breedInput;
   QLineEdit *nameInput;
   QLineEdit *ageInput;
   QLineEdit *linkInput;
};



#endif //ADDDOGDIALOG_H
