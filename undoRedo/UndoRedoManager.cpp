

#include "UndoRedoManager.h"

#include <QMessageBox>
void UndoRedoManager::executeCommand(std::unique_ptr<ICommand> command) {
    command->execute();
    undoStack.push(std::move(command));
    while ( !redoStack.empty()) { // Clear redo stack on new command
        redoStack.pop();
    }

}
bool UndoRedoManager::undo() {
    if (undoStack.empty()) {
        QMessageBox::warning(nullptr, "Warning", "No commands to undo.");
        return false;
    }
    std::unique_ptr<ICommand> command = std::move(undoStack.top());
    undoStack.pop();
    command->undo();
    redoStack.push(std::move(command));
    return true;
}

bool UndoRedoManager::redo() {
    if (redoStack.empty()) {
        QMessageBox::warning(nullptr, "Warning", "No commands to redo.");
        return false;
    }
    std::unique_ptr<ICommand> command = std::move(redoStack.top());
    redoStack.pop();
    command->execute();
    undoStack.push(std::move(command));
    return true;
}