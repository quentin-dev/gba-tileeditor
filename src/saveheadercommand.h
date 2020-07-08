#ifndef SAVEHEADERCOMMAND_H
#define SAVEHEADERCOMMAND_H

#include "command.h"

class SaveHeaderCommand : public Command
{
public:
    SaveHeaderCommand() = default;
    ~SaveHeaderCommand() = default;

    void execute(Map& map, const std::string& filename) override final
    {
        map.write_data(filename, true);
    }
};

#endif // SAVEHEADERCOMMAND_H
