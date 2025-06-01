//
// Created by mures on 5/11/2025.
//
#pragma once
#ifndef REMOVEDOGDIALOG_H
#define REMOVEDOGDIALOG_H
#include <QDialog>
#include "gui/MainWindow.h"
#include <QLineEdit>
#include <QPushButton>
#include "service/service.h"


class RemoveDogDialog : public QDialog{
    Q_OBJECT


    public:
    RemoveDogDialog(Service& service, QWidget *parent = nullptr);

    private slots:
    void handleRemove();

private:
    Service& service;
    QLineEdit *breedInput;
    QLineEdit *nameInput;
    QLineEdit *ageInput;
    QLineEdit *linkInput;
};





#endif //REMOVEDOGDIALOG_H