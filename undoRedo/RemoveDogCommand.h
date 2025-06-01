#pragma once

#include "ICommand.h"
#include "../repository/Repo.h"
class RemoveDogCommand: public ICommand {
private:
    Dog dogToRemove;
    TextFileRepository& repo;
public:
    RemoveDogCommand(const Dog& dog, TextFileRepository& repo): dogToRemove(dog), repo(repo) {};

    void execute() override {
        repo.remove(dogToRemove);
    }
    void undo() override {
        repo.add(dogToRemove);
    }
};