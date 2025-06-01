// File: `src/exceptions/CustomExceptions.h`
#ifndef CUSTOM_EXCEPTIONS_H
#define CUSTOM_EXCEPTIONS_H

#include <stdexcept>
#include <string>

class RepositoryException : public std::runtime_error {
public:
    explicit RepositoryException(const std::string& message) : std::runtime_error(message) {}
};

class ValidationException : public std::runtime_error {
public:
    explicit ValidationException(const std::string& message) : std::runtime_error(message) {}
};

class InputException : public std::runtime_error {
public:
    explicit InputException(const std::string& message) : std::runtime_error(message) {}
};

#endif // CUSTOM_EXCEPTIONS_H