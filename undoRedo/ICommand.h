#pragma once


#include <memory>
#include "../domain/Dog.h"

class ICommand {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~ICommand() = default;

};
