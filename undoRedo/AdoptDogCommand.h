#pragma once
#include "ICommand.h"
#include "../adoption/AdoptionList.h" // Or your adopted dogs container/service header
#include <algorithm> // For std::find_if()>
class AdoptDogCommand : public ICommand {
private:
    Dog dogToAdopt;
    std::vector<Dog>& adoptedDogsList; // reference to your adopted dogs container

public:
    AdoptDogCommand(const Dog& dog, std::vector<Dog>& adoptedDogs)
        : dogToAdopt(dog), adoptedDogsList(adoptedDogs) {}

    void execute() override {
        adoptedDogsList.push_back(dogToAdopt);
    }

    void undo() override {
        // Remove the dog from adoptedDogsList
        auto it = std::find_if(adoptedDogsList.begin(), adoptedDogsList.end(),
                               [&](const Dog& d) {
                                   return d.getBreed() == dogToAdopt.getBreed() &&
                                          d.getName() == dogToAdopt.getName() &&
                                          d.getAge() == dogToAdopt.getAge() &&
                                          d.getPhotography() == dogToAdopt.getPhotography();
                               });
        if (it != adoptedDogsList.end()) {
            adoptedDogsList.erase(it);
        }
    }
};
