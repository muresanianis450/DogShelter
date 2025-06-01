#include "service.h"
#include "../validator/validator.h"
#include "../exceptions/CustomExceptions.h"
#include "undoRedo/AddDogCommand.h"    // Include command headers
#include "undoRedo/RemoveDogCommand.h"
#include "undoRedo/UpdateDogCommand.h"
#include <QMessageBox> // For error messages, if you want them here too
#include "undoRedo/AdoptDogCommand.h"
//Constructor
Service::Service(): repo(TextFileRepository("dogs.txt")) {
    this->adoptedDogs = std::vector<Dog>();
}

bool Service::invalidDog(const Dog& d) {
    try {
        Validator::validateDog(d);  // Try to validate the dog
        return false;  // If no exception, dog is valid
    } catch (const std::invalid_argument& e) {
        return true;  // If validation fails, dog is invalid
    }
}

void Service::addDog(const Dog& d) {
    try {
        Validator::validateDog(d);
        // Instead of directly adding, create and execute a command
        std::unique_ptr<ICommand> command = std::make_unique<AddDogCommand>(d, this->repo);
        undoRedoManager.executeCommand(std::move(command));
    } catch (const ValidationException& e) {
        throw; // Re-throw validation exception
    } catch (const RepositoryException& e) {
        throw; // Re-throw repository exception
    }
}

// Changed return type to void and removed return statement
void Service::removeDog(const Dog& d) {
    // Check if the dog exists before attempting to remove
    std::vector<Dog> allDogs = repo.getAll();
    bool dogExists = false;
    for (const auto& existingDog : allDogs) {
        if (existingDog.getBreed() == d.getBreed() &&
            existingDog.getName() == d.getName() &&
            existingDog.getAge() == d.getAge() &&
            existingDog.getPhotography() == d.getPhotography()) {
            dogExists = true;
            break;
        }
    }

    if (!dogExists) {
        throw RepositoryException("Dog not found in the database!");
    }

    // Create and execute a RemoveDogCommand
    std::unique_ptr<ICommand> command = std::make_unique<RemoveDogCommand>(d, this->repo);
    undoRedoManager.executeCommand(std::move(command));
    // No return needed as function is now void
}

// Changed return type to void and removed return statement
void Service::updateDog(const Dog& oldDog, const Dog& newDog) {
    try {
        Validator::validateDog(newDog); // Validate the new dog
        // Check if the old dog exists before attempting to update
        std::vector<Dog> allDogs = repo.getAll();
        bool oldDogExists = false;
        for (const auto& existingDog : allDogs) {
            if (existingDog.getBreed() == oldDog.getBreed() &&
                existingDog.getName() == oldDog.getName() &&
                existingDog.getAge() == oldDog.getAge() &&
                existingDog.getPhotography() == oldDog.getPhotography()) {
                oldDogExists = true;
                break;
            }
        }

        if (!oldDogExists) {
            throw RepositoryException("Old dog not found in the database for update!");
        }

        // Create and execute an UpdateDogCommand
        std::unique_ptr<ICommand> command = std::make_unique<UpdateDogCommand>(oldDog, newDog, this->repo);
        undoRedoManager.executeCommand(std::move(command));
        // No return needed as function is now void
    } catch (const ValidationException& e) {
        throw; // Re-throw validation exception
    } catch (const RepositoryException& e) {
        throw; // Re-throw repository exception
    }
}

std::vector<Dog> Service::getAdoptedDogs() const {
    return this->adoptedDogs;
}

std::vector<Dog> Service::getAllDogs() const {
    return this->repo.getAll();
}

std::vector<Dog> Service::getDogsByBreed(const std::string& breed) const {
    std::vector<Dog> dogs = this->repo.getAll();
    std::vector<Dog> dogsByBreed;
    for (const Dog& dog : dogs) {
        if (dog.getBreed() == breed) {
            dogsByBreed.push_back(dog);
        }
    }
    return dogsByBreed;
}

void Service::adoptDog(const Dog& d) {
    // Create an AdoptDogCommand and execute it via undoRedoManager
    std::unique_ptr<ICommand> command = std::make_unique<AdoptDogCommand>(d, this->adoptedDogs);
    undoRedoManager.executeCommand(std::move(command));
}

bool Service::undo() {
   return undoRedoManager.undo();
}

bool Service::redo() {
    return undoRedoManager.redo();
}