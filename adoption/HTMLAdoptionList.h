// File: `src/adoption/HTMLAdoptionList.h`
#ifndef HTML_ADOPTION_LIST_H
#define HTML_ADOPTION_LIST_H

#include "AdoptionList.h"
#include <fstream>
#include <regex>
#include <stdexcept>

class HTMLAdoptionList : public AdoptionList {
public:
    void saveToFile(const std::string& filename) const override {
        std::ofstream fout(filename,std::ios::app);
        if (!fout.is_open()) {
            throw std::runtime_error("Could not open file: " + filename);
        }

        fout << "<!DOCTYPE html>\n<html>\n<head>\n<title>Adoption List</title>\n</head>\n<body>\n";
        fout << "<table border=\"1\">\n<tr><th>Name</th><th>Breed</th><th>Age</th><th>Photography</th></tr>\n";

        for (const auto& dog : adoptedDogs) {
            fout << "<tr><td>" << dog.getName() << "</td><td>" << dog.getBreed() << "</td><td>"
                 << dog.getAge() << "</td><td><a href=\"" << dog.getPhotography()
                 << "\">Link</a></td></tr>\n";
        }

        fout << "</table>\n</body>\n</html>\n";

        fout.close();
    }

    void loadFromFile(const std::string& filename) override {
        std::ifstream fin(filename);
        if (!fin.is_open()) {
            return; // If the file doesn't exist, start with an empty list
        }

        std::string line;
        std::regex rowRegex(R"regex(<tr><td>(.*?)</td><td>(.*?)</td><td>(.*?)</td><td><a href="(.*?)">)regex");
        std::smatch match;

        while (std::getline(fin, line)) {
            if (std::regex_search(line, match, rowRegex)) {
                std::string name = match[1];
                std::string breed = match[2];
                int age = std::stoi(match[3]);
                std::string photography = match[4];
                adoptedDogs.emplace_back(name, breed, age, photography);
            }
        }

        fin.close();
    }
};

#endif // HTML_ADOPTION_LIST_H