#ifndef __READLINE_WRAP_H__
#define __READLINE_WRAP_H__

#include <memory>
#include <string>
#include <string.h>
#include <vector>
#include <stdio.h>
// #include "Command.h"


extern "C" {

#ifdef READLINE_LIBRARY
#  include "readline.h"
#  include "history.h"
#else
#  include <readline/readline.h>
#  include <readline/history.h>
#endif

extern char *xmalloc PARAMS((size_t));

}

#define READLINE_NAME "CliClient >"

class Command;

class ReadlineWrap
{
    public:
        static std::shared_ptr<ReadlineWrap>& getInstance();
        void addCommands(const std::vector<Command> &vecCmds);
        void runReadline();
        void stopReadline();
        void printAllCmdHelp();

    private:
        ReadlineWrap();
        ~ReadlineWrap() = default;
        void initialize();
        int execute(char *line);
        Command & getCommand(const std::string & cmdName);
        static char * generator(const char *text, int state);
        static char ** completion(const char* text, int start, int end);

    private:
        bool isRuningFlag;
        static std::vector<Command> vecCommands;
        static std::shared_ptr<ReadlineWrap> instance;
};



#endif //__READLINE_WRAP_H__