#pragma once

#include "ICommand.h"
#include "../repository/Repo.h"
class AddDogCommand: public ICommand {
private:
    Dog dogToAdd;
    TextFileRepository& repo;
public:
    AddDogCommand(const Dog& dog, TextFileRepository& repo): dogToAdd(dog), repo(repo) {};

    void execute() override {
        repo.add(dogToAdd);
    }
    void undo() override {
        repo.remove(dogToAdd);
    }
};