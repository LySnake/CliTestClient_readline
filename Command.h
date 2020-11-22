#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <functional>
#include <string>
#include <string.h>

#include "ReadlineWrap.h"

using EXEC_CMD_FUNC = int(const std::string &, const std::string &);

class Command
{
    public:
        Command(std::string name, EXEC_CMD_FUNC func, std::string doc, std::string help);
        ~Command() = default;
        const std::string &getCmdName();
        const std::string &getCmdDoc();
        const std::string &getCmdHelp();
        int runCmd(const std::string &cmdName, const std::string &args); 
    private:
        std::string CmdName;
        std::function<EXEC_CMD_FUNC> CmdFunc;
        std::string CmdDoc;
        std::string CmdHelp;
};

#endif //__COMMAND_H__