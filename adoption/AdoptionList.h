#ifndef ADOPTION_LIST_H
#define ADOPTION_LIST_H

#include "../domain/Dog.h"
#include <vector>
#include <string>

class AdoptionList {
protected:
    std::vector<Dog> adoptedDogs;

public:
    virtual ~AdoptionList() = default;

    void addDog(const Dog& dog) {
        adoptedDogs.push_back(dog);
    }
    void removeDog(const Dog& dog) {
        for (auto it = adoptedDogs.begin(); it != adoptedDogs.end(); ++it) {
            if (*it == dog) {
                adoptedDogs.erase(it);
                break;
            }
        }
    }

    virtual void saveToFile(const std::string& filename) const = 0;
    virtual void loadFromFile(const std::string& filename) = 0;

    const std::vector<Dog>& getAdoptedDogs() const {
        return adoptedDogs;
    }
};

#endif // ADOPTION_LIST_H