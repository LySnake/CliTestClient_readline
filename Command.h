#ifndef __COMMAND_H__
#define __COMMAND_H__


#include <functional>
#include <string>
#include <string.h>


#ifdef READLINE_LIBRARY
#  include "readline.h"
#  include "history.h"
#else
#  include <readline/readline.h>
#  include <readline/history.h>
#endif

using RL_ICPFUNC_T = std::function<rl_icpfunc_t>;

class Command
{
    public:
        Command(std::string name, rl_icpfunc_t func, std::string doc, std::string help);
        ~Command() = default;
        const std::string &getCmdName();
        const std::string &getCmdDoc();
        const std::string &getCmdHelp();
        int runCmd(char *line); 
    private:
        std::string CmdName;
        RL_ICPFUNC_T CmdFunc;
        std::string CmdDoc;
        std::string CmdHelp;
};

#endif //__COMMAND_H__