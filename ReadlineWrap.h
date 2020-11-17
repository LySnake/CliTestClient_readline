#ifndef __READLINE_WRAP_H__
#define __READLINE_WRAP_H__

#include <memory>
#include <string>
#include <string.h>
#include <vector>
#include "Command.h"


#define READLINE_NAME "CliClient >"


class ReadlineWrap
{
    public:
        static std::shared_ptr<ReadlineWrap>& getInstance();
        void addCommand(Command &cmd);
        void runReadline();
        void stopReadline();

    private:
        ReadlineWrap();
        ~ReadlineWrap() = default;
        void initialize();
        int execute(char *line);
        Command & getCommand(char *name);
        static char * generator(const char *text, int state);
        static char ** completion(const char* text, int start, int end);

    private:
        bool isRuningFlag;
        static std::vector<Command> vecCommands;
        static std::shared_ptr<ReadlineWrap> instance;
};



#endif //__READLINE_WRAP_H__