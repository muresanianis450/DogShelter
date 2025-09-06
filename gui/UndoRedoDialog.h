#pragma once
#ifndef UNDOREDODIALOG_H
#define UNDOREDODIALOG_H

#include <QDialog>
#include <QPushButton>
#include "../service/Service.h"

class UndoRedoDialog : public QDialog {
    Q_OBJECT
private:
    Service& service;
    QPushButton* undoButton;
    QPushButton* redoButton;

public:
    explicit UndoRedoDialog(Service& srv, QWidget* parent = nullptr);

    private slots:
        void undo();
    void redo();
};

#endif // UNDOREDODIALOG_H
