#include "CommandList.h"


int cmd_exit(char * args)
{
    ReadlineWrap::getInstance()->stopReadline();
    return 0;
}

int cmd_not_exist(char * args)
{
    printf("not exist");
    return 0;
}



Command cmd_fail = Command("not exist cmd", cmd_not_exist, "cmd_not_exist ", "cmd_not_exist ");

void initializeCommands()
{
    Command do_exit = Command("exit", 
                                                    cmd_exit, 
                                                    "exit_doc", 
                                                    "exit_help");
    ReadlineWrap::getInstance()->addCommand(do_exit);
}
