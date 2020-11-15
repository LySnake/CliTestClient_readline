#include <readline/readline.h>
#include <readline/history.h>
#include <memory>
#include <string>
#include <list>
#include <functional>

#define READLINE_NAME "CliClient >"

using RL_ICPFUNC_T = std::function<rl_icpfunc_t>;

class ReadlineWrap
{
    public:
        class COMMAND
        {
            public:
                COMMAND(std::string name, rl_icpfunc_t *func, std::string doc, std::string help);
                ~COMMAND() = default;
                inline const std::string &getCmdName();
                inline const std::string &getCmdDoc();
                inline const std::string &getCmdHelp();
            private:
                std::string CmdName;
                RL_ICPFUNC_T CmdFunc;
                std::string CmdDoc;
                std::string CmdHelp;
        };
        

    public:
        std::shared_ptr<ReadlineWrap>& getInstance();
        void addCommand(COMMAND &cmd);

    private:
        ReadlineWrap();
        ~ReadlineWrap() = default;
        void initialize();
        static char * generator(const char *text, int state);
        static char ** completion(const char* text, int start, int end);

    private:
        static std::list<COMMAND> listCommands;
        static std::shared_ptr<ReadlineWrap> instance;
};

