// File: `src/validator/validator.cpp`
#include "validator.h"
#include "../exceptions/CustomExceptions.h"

void Validator::validateDog(const Dog& d) {
    if (d.getName().empty()) {
        throw ValidationException("Dog name cannot be empty.");
    }
    if (d.getBreed().empty()) {
        throw ValidationException("Dog breed cannot be empty.");
    }
    if (d.getAge() <= 0) {
        throw ValidationException("Dog age must be greater than 0.");
    }
    if (d.getPhotography().empty()) {
        throw ValidationException("Dog photography link cannot be empty.");
    }
}