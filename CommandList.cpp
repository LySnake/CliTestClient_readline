#include <unistd.h>
#include <linux/limits.h>
#include <errno.h>
#include <unistd.h>
#include <vector>

#include "CommandList.h"
#include "spdlog/spdlog.h"

extern HIST_ENTRY **history_list ();

static int func_history(const std::string &cmdName, const std::string &args)
{
    HIST_ENTRY **list;
    register int i;

    list = history_list ();
    if (list)
    {
        for (i = 0; list[i]; i++)
        {
            spdlog::info("{:3d}: {}", i, list[i]->line);
        }
    }
    return 0;
}

static int func_exit(const std::string &cmdName, const std::string &args)
{
    ReadlineWrap::getInstance()->stopReadline();
    return 0;
}

static int func_cd(const std::string &cmdName, const std::string &args)
{
    if(chdir(args.c_str())) {
        spdlog::info("chdir fail: {}", strerror(errno));
        return -1;
    }
    return 0;
}

static int func_pwd(const std::string &cmdName, const std::string &args)
{     
    char cwd[PATH_MAX];
    if( !getcwd(cwd, sizeof(cwd)))
    {
        spdlog::info("getcwd fail: {}", strerror(errno));
        return -1;
    }
    spdlog::info("{}", cwd);
    return 0;
}

static int func_not_exist(const std::string &cmdName, const std::string &args)
{   
    std::string cmd = cmdName;
    cmd += " ";
    cmd += args;
    if(system(cmd.c_str()) == -1) {
        spdlog::info("shell command fail. {}", strerror(errno));
        return -1;
    }
    return 0;
}

static int func_help(const std::string &cmdHelp, const std::string &args)
{
    ReadlineWrap::getInstance()->printAllCmdHelp();
    return 0;
}


Command cmd_fail = Command("__not_exist_cmd__", func_not_exist, "", "");

void initializeCommands()
{
    std::vector<Command> vecCommands = {
        {
            "pwd", 
            func_pwd, 
            "Prints the current working directory.", 
            "usag: pwd"
        },
        {
            "cd", 
            func_cd, 
            "change work directory.", 
            "usag: cd directory."
        },
        {
            "exit", 
            func_exit, 
            "exit program.", 
            "usag: exit"
        },
        {
            "history",
            func_history,
            "print command history.",
            "usag: history"
        },
        {
            "help",
            func_help,
            "print all command help infomation",
            "usag: help"
        }
    };
                            
    ReadlineWrap::getInstance()->addCommands(vecCommands);
}
