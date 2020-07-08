#ifndef SAVESOURCESCOMMAND_H
#define SAVESOURCESCOMMAND_H

#include "command.h"

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

#endif // SAVESOURCESCOMMAND_H
