#include <unistd.h>
#include <linux/limits.h>
#include <errno.h>
#include <unistd.h>

#include "CommandList.h"
#include "spdlog/spdlog.h"


int func_exit(const std::string &cmdName, const std::string &args)
{
    ReadlineWrap::getInstance()->stopReadline();
    return 0;
}

int func_cd(const std::string &cmdName, const std::string &args)
{
    if(chdir(args.c_str())) {
        spdlog::info("chdir fail: {}\n", strerror(errno));
        return -1;
    }
    return 0;
}

int func_pwd(const std::string &cmdName, const std::string &args)
{     
    char cwd[PATH_MAX];
    if( !getcwd(cwd, sizeof(cwd)))
    {
        spdlog::info("getcwd fail: {}\n", strerror(errno));
        return -1;
    }
    spdlog::info("{}\n", cwd);
    return 0;
}

int func_not_exist(const std::string &cmdName, const std::string &args)
{   
    std::string cmd = cmdName;
    cmd += " ";
    cmd += args;
    if(system(cmd.c_str()) == -1) {
        spdlog::info("shell command fail. {}\n", strerror(errno));
        return -1;
    }
    return 0;
}


Command cmd_fail = Command("__not_exist_cmd__", func_not_exist, "", "");

void initializeCommands()
{
    Command cmd_exit = Command("exit", 
                            func_exit, 
                            "exit program.", 
                            "usag: exit");
    Command cmd_cd = Command("cd", 
                            func_cd, 
                            "change work directory.", 
                            "usag: cd directory.");
    Command cmd_pwd = Command("pwd", 
                            func_pwd, 
                            "Prints the current working directory.", 
                            "usag: pwd");

                            
    ReadlineWrap::getInstance()->addCommand(cmd_exit);
    ReadlineWrap::getInstance()->addCommand(cmd_cd);
    ReadlineWrap::getInstance()->addCommand(cmd_pwd);
}
