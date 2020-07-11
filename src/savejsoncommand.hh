#ifndef SAVEJSONCOMMAND_HH
#define SAVEJSONCOMMAND_HH

#include "command.hh"

class SaveJsonCommand : public Command
{
public:
    SaveJsonCommand() = default;
    ~SaveJsonCommand() = default;

    void execute(Map& map, const std::string& filename) override final
    {
        map.to_json_file(filename);
    }
};

#endif // SAVEJSONCOMMAND_H
