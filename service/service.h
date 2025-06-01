#pragma once
#ifndef SERVICE_H
#define SERVICE_H

#include "../repository/Repo.h"
#include "../domain/Dog.h"
#include <vector>
#include <string>
#include "undoRedo/UndoRedoManager.h" // Include the new manager

class Service {
private:
    TextFileRepository repo;
    std::vector<Dog> adoptedDogs;
    UndoRedoManager undoRedoManager; // Add UndoRedoManager

    // Explicitly disable copying of Service instances
    // This prevents attempts to copy undoRedoManager which contains unique_ptrs
    Service(const Service&) = delete;
    Service& operator=(const Service&) = delete;

public:
    Service();

    void addDog(const Dog& d);
    void removeDog(const Dog& d); // Changed return type to void
    void updateDog(const Dog& oldDog, const Dog& newDog); // Changed return type to void

    std::vector<Dog> getAllDogs() const;
    std::vector<Dog> getDogsByBreed(const std::string& breed) const;
    void adoptDog(const Dog& d);
    std::vector<Dog> getAdoptedDogs() const; // Existing function

    // New methods for undo/redo
    bool undo();
    bool redo();
    bool canUndo() const { return undoRedoManager.canUndo(); }
    bool canRedo() const { return undoRedoManager.canRedo(); }

private:
    bool invalidDog(const Dog& d); // Keep as private helper if needed
};

#endif //SERVICE_H