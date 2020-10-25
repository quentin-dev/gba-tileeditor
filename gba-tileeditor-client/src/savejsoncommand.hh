#pragma once

#include "command.hh"

/// A Command class to save a map as a JSON file
class SaveJsonCommand : public Command
{
public:
    /// @brief SaveJsonCommand constructor
    SaveJsonCommand() = default;

    /// @brief SaveJsonCommand destructor
    ~SaveJsonCommand() = default;

    /// @brief Save the given map as a JSON file called filename
    /// @param map: the map to serialize
    /// @param filename: the name of the JSON file to create / update
    /// @return nothing
    void execute(Map& map, const std::string& filename) override final
    {
        map.to_json_file(filename);
    }
};
