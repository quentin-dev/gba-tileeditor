#pragma once

#include <string>

#include "map.hh"

/// A typical "Command" class according to the command design pattern
class Command
{
public:
    /// @brief Command constructor
    virtual ~Command()
    {}

    /// @brief execute the command on a given Map and file
    /// @param map: the map to execute the command on
    /// @param filename: the filename to create or update
    /// @return nothing
    virtual void execute(Map& map, const std::string& filename) = 0;
};
