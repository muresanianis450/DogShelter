#include "UndoRedoDialog.h"
#include <QVBoxLayout>
#include <QMessageBox>

UndoRedoDialog::UndoRedoDialog(Service& srv, QWidget* parent)
    : QDialog(parent), service(srv) {

    setWindowTitle("Undo / Redo");

    undoButton = new QPushButton("Undo", this);
    redoButton = new QPushButton("Redo", this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(undoButton);
    layout->addWidget(redoButton);

    connect(undoButton, &QPushButton::clicked, this, &UndoRedoDialog::undo);
    connect(redoButton, &QPushButton::clicked, this, &UndoRedoDialog::redo);

    setLayout(layout);
}

void UndoRedoDialog::undo() {
    if (service.undo()) {
        QMessageBox::information(this, "Undo", "Last operation undone");
    }
    // service.undo() shows warning if nothing to undo
}

void UndoRedoDialog::redo() {
    if (service.redo()) {
        QMessageBox::information(this, "Redo", "Last operation redone");
    }
    // service.redo() shows warning if nothing to redo
}
