#pragma once

#include "command.hh"

/// A Command class to save a map's header
class SaveHeaderCommand : public Command
{
public:
    /// @brief SaveHeaderCommand constructor
    SaveHeaderCommand() = default;

    /// @brief SaveHeaderCommand destructor
    ~SaveHeaderCommand() = default;

    /// @brief save the given map's header to filename
    /// @param map: the map to save
    /// @param filename: the filename to write to
    /// @return nothing
    void execute(Map& map, const std::string& filename) override final
    {
        map.write_data(filename, true);
    }
};
