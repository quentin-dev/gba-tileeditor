#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include "map.h"

class Command
{
    public:
        virtual ~Command() {}
        virtual void execute(Map &map, const std::string &filename) = 0;
};

#endif // COMMAND_H
