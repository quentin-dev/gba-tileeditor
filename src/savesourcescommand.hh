#ifndef SAVESOURCESCOMMAND_HH
#define SAVESOURCESCOMMAND_HH

#include "command.hh"

class SaveSourcesCommand : public Command
{
public:
    SaveSourcesCommand() = default;
    ~SaveSourcesCommand() = default;

    void execute(Map& map, const std::string& filename) override final
    {
        map.write(filename);
    }
};

#endif // SAVESOURCESCOMMAND_HH
