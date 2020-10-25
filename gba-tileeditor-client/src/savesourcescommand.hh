#pragma once

#include "command.hh"

/// A Command class to save a map's content as a source file
class SaveSourcesCommand : public Command
{
public:
    /// @brief SaveSourcesCommand constructor
    SaveSourcesCommand() = default;

    /// @brief SaveSourcesCommand destructor
    ~SaveSourcesCommand() = default;

    /// @brief save the given map's content as a source file
    /// @param map: the map to save
    /// @param filename: the filename to write to
    /// @return nothing
    void execute(Map& map, const std::string& filename) override final
    {
        map.write(filename);
    }
};
