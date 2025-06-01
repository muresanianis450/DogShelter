//
// Created by mures on 5/11/2025.
//
#pragma once
#ifndef MAINWINDOW_H

#define MAINWINDOW_H

#include "UndoRedoDialog.h"
#include "../adoption/AdoptionListFactory.h"
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "../service/service.h"
#include <QShortcut> // For keyboard shortcuts

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(Service& service ,QWidget *parent = nullptr);
    private slots:
        void goToModePage() const;
    void goToAdminPage();
    void goToUserPage(); // Moved here for consistency
    void onShowAdoptedDogsClicked();
    void undoLastOperation(); // New slot for undo
    void redoLastOperation(); // New slot for redo

private:

    UndoRedoDialog* undoRedoDialog = nullptr;
    Service& service;
    QStackedWidget *stackedWidget;
    std::string whereToSaveFile;
    // std::unique_ptr<AdoptionList> adoptionList; // This might not be needed directly in MainWindow anymore if ShowAllAdoptedDialog handles it

    QWidget  *createStartPage();
    QWidget *createModePage();
    QWidget *createUserPage();
    QWidget *createAdminPage();

    // New for undo/redo
    QPushButton *undoButton;
    QPushButton *redoButton;
    QShortcut *undoShortcut;
    QShortcut *redoShortcut;

    void setupShortcuts(); // Helper to set up shortcuts
};



#endif //MAINWINDOW_H