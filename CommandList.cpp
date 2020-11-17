#include <unistd.h>
#include <linux/limits.h>
#include <errno.h>
#include <unistd.h>

#include "CommandList.h"


int func_exit(char * args)
{
    ReadlineWrap::getInstance()->stopReadline();
    return 0;
}

int func_cd(char * args)
{
    chdir(args);
    return 0;
}

int func_pwd(char *args)
{     
    char cwd[PATH_MAX];
    if( !getcwd(cwd, sizeof(cwd)))
    {
        printf("getcwd fail: %s\n", strerror(errno));
        return -1;
    }
    printf("%s\n", cwd);
    return 0;
}

int func_not_exist(char * args)
{
    printf("Command does not exist.\n");
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
