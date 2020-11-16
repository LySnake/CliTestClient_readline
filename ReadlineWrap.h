#ifndef __READLINE_WRAP_H__
#define __READLINE_WRAP_H__

#include <memory>
#include <string>
#include <string.h>
#include <vector>
#include <functional>


#ifdef READLINE_LIBRARY
#  include "readline.h"
#  include "history.h"
#else
#  include <readline/readline.h>
#  include <readline/history.h>
#endif

#define READLINE_NAME "CliClient >"

using RL_ICPFUNC_T = std::function<rl_icpfunc_t>;

class ReadlineWrap
{
    public:
        class COMMAND
        {
            public:
                COMMAND(std::string name, rl_icpfunc_t func, std::string doc, std::string help);
                ~COMMAND() = default;
                inline const std::string &getCmdName();
                inline const std::string &getCmdDoc();
                inline const std::string &getCmdHelp();
                inline int runCmd(char *line); 
            private:
                std::string CmdName;
                RL_ICPFUNC_T CmdFunc;
                std::string CmdDoc;
                std::string CmdHelp;
        };
        

    public:
        static std::shared_ptr<ReadlineWrap>& getInstance();
        void addCommand(COMMAND &cmd);
        void runReadline();
        void stopReadline();

    private:
        ReadlineWrap();
        ~ReadlineWrap() = default;
        void initialize();
        int execute(char *line);
        COMMAND & getCommand(char *name);
        static char * generator(const char *text, int state);
        static char ** completion(const char* text, int start, int end);

    private:
        bool isRuningFlag;
        static std::vector<COMMAND> vecCommands;
        static std::shared_ptr<ReadlineWrap> instance;
};



#endif //__READLINE_WRAP_H__