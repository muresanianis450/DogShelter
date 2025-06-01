// File: `src/adoption/AdoptionListFactory.h`
#ifndef ADOPTION_LIST_FACTORY_H
#define ADOPTION_LIST_FACTORY_H

#include "CSVAdoptionList.h"
#include "HTMLAdoptionList.h"

class AdoptionListFactory {
public:
    static std::unique_ptr<AdoptionList> createAdoptionList(const std::string& type) {
        std::unique_ptr<AdoptionList> adoptionList;

        if (type == "CSV") {
            adoptionList = std::make_unique<CSVAdoptionList>();
            adoptionList->loadFromFile("adoption_list.csv");
        } else if (type == "HTML") {
            adoptionList = std::make_unique<HTMLAdoptionList>();
            adoptionList->loadFromFile("adoption_list.html");
        } else {
            throw std::invalid_argument("Invalid adoption list type: " + type);
        }

        return adoptionList;
    }
};

#endif // ADOPTION_LIST_FACTORY_H