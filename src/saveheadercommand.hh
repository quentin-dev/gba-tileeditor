#ifndef SAVEHEADERCOMMAND_HH
#define SAVEHEADERCOMMAND_HH

#include "command.hh"

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

#endif // SAVEHEADERCOMMAND_HH
