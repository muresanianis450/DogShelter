#pragma once
#ifndef UNDOREDOMANAGER_H
#define UNDOREDOMANAGER_H

#include <stack>
#include <memory>
#include "ICommand.h"

class UndoRedoManager {
private:
    std::stack<std::unique_ptr<ICommand>> undoStack;
    std::stack<std::unique_ptr<ICommand>> redoStack;

public:
    UndoRedoManager() = default; // Default constructor
    // Disable copying because std::unique_ptr is not copyable
    UndoRedoManager(const UndoRedoManager&) = delete;
    UndoRedoManager& operator=(const UndoRedoManager&) = delete;
    // Enable moving (if you need to move UndoRedoManager instances)
    UndoRedoManager(UndoRedoManager&&) = default;
    UndoRedoManager& operator=(UndoRedoManager&&) = default;

    void executeCommand(std::unique_ptr<ICommand> command);
    bool undo();
    bool redo();
    bool canUndo() const { return !undoStack.empty(); }
    bool canRedo() const { return !redoStack.empty(); }
};

#endif // UNDOREDOMANAGER_H