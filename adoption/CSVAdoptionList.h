// File: `src/adoption/CSVAdoptionList.h`
#ifndef CSV_ADOPTION_LIST_H
#define CSV_ADOPTION_LIST_H

#include "AdoptionList.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

class CSVAdoptionList : public AdoptionList {
public:
    void saveToFile(const std::string& filename) const override {
        std::ofstream fout(filename, std::ios::app); // Open in append mode
        if (!fout.is_open()) {
            throw std::runtime_error("Could not open file: " + filename);
        }

        for (const auto& dog : adoptedDogs) {
            fout << dog.getName() << "," << dog.getBreed() << ","
                 << dog.getAge() << "," << dog.getPhotography() << "\n";
        }

        fout.close();
    }

    void loadFromFile(const std::string& filename) override {
        std::ifstream fin(filename);
        if (!fin.is_open()) {
            return; // If the file doesn't exist, start with an empty list
        }

        std::string line;
        while (std::getline(fin, line)) {
            std::stringstream ss(line);
            std::string name, breed, ageStr, photography;

            if (!std::getline(ss, name, ',')) continue;
            if (!std::getline(ss, breed, ',')) continue;
            if (!std::getline(ss, ageStr, ',')) continue;
            if (!std::getline(ss, photography, ',')) continue;

            int age = std::stoi(ageStr);
            adoptedDogs.emplace_back(name, breed, age, photography);
        }

        fin.close();
    }
};

#endif // CSV_ADOPTION_LIST_H