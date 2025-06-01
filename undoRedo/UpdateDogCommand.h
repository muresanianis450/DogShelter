#pragma once


#include "ICommand.h"
#include "../repository/Repo.h"

class UpdateDogCommand: public ICommand {


private:
    Dog oldDog;
    Dog newDog;
    TextFileRepository& repo;

public:
    UpdateDogCommand(const Dog& oldDog, const Dog& newDog, TextFileRepository& repo): oldDog(oldDog), newDog(newDog), repo(repo) {};
    void execute() override {
        repo.update(oldDog, newDog);
    }
    void undo() override {
        repo.update(newDog, oldDog);
    }
};