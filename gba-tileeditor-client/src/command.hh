#ifndef COMMAND_HH
#define COMMAND_HH

#include <string>

#include "map.hh"

class Command
{
public:
    virtual ~Command()
    {}
    virtual void execute(Map& map, const std::string& filename) = 0;
};

#endif // COMMAND_HH
