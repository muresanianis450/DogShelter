// File: `src/repository/Repo.h`
#ifndef REPO_H
#define REPO_H

#include "../domain/Dog.h"
#include "../exceptions/CustomExceptions.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <string>

class MemoryRepository {
protected:
    std::vector<Dog> elements;
public:
    MemoryRepository() = default;
    virtual ~MemoryRepository() = default;

    virtual void add(const Dog& e) {
        for (const auto& elem : elements) {
            if (elem == e) {
                throw RepositoryException("Dog already exists in the repository.");
            }
        }
        elements.push_back(e);
    }

    virtual bool remove(const Dog& e) {
        auto it = std::find(elements.begin(), elements.end(), e);
        if (it == elements.end()) {
            throw RepositoryException("Dog does not exist in the repository.");
        }
        elements.erase(it);
        return true;
    }

    virtual bool update(const Dog& oldElem, const Dog& newElem) {
        auto it = std::find(elements.begin(), elements.end(), oldElem);
        if (it == elements.end()) {
            throw RepositoryException("Dog to update does not exist in the repository.");
        }
        *it = newElem;
        return true;
    }

    virtual std::vector<Dog> getAll() const {
        return elements;
    }
};

class TextFileRepository : public MemoryRepository {
private:
    std::string filename;

    void loadFromFile() {
        elements.clear();
        std::ifstream fin(filename);
        if (!fin.is_open()) {
            // File does not exist; start with an empty repository.
            return;
        }
        std::string line;
        while (std::getline(fin, line)) {
            std::stringstream ss(line);
            std::string name, breed, ageStr, photography;
            if (!std::getline(ss, breed, ',')) continue;
            if (!std::getline(ss, name, ',')) continue;
            if (!std::getline(ss, ageStr, ',')) continue;
            if (!std::getline(ss, photography, '~')) continue;
            try {
                int age = std::stoi(ageStr);
                Dog dog(name, breed, age, photography);
                elements.push_back(dog);
            } catch (const std::exception&) {
                // Skip invalid lines.
                continue;
            }
        }
        fin.close();
    }

    void saveToFile() const {
        std::ofstream fout(filename);
        if (!fout.is_open()) {
            throw RepositoryException("Could not open file: " + filename);
        }
        for (const auto& dog : elements) {
            fout << dog.getBreed() << "," << dog.getName() << ","
                 << dog.getAge() << "," << dog.getPhotography() << "~\n";
        }
        fout.close();
    }

public:
    explicit TextFileRepository(const std::string& file) : filename(file) {
        loadFromFile();
    }

    void add(const Dog& e) override {
        MemoryRepository::add(e);
        saveToFile();
    }

    bool remove(const Dog& e) override {
        bool res = MemoryRepository::remove(e);
        saveToFile();
        return res;
    }

    bool update(const Dog& oldElem, const Dog& newElem) override {
        bool res = MemoryRepository::update(oldElem, newElem);
        saveToFile();
        return res;
    }
};

#endif // REPO_H