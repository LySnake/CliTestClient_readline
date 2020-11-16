#include "Commands.h"


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



COMMAND cmd_fail = COMMAND("not exist cmd", cmd_not_exist, "cmd_not_exist ", "cmd_not_exist ");

void initializeCommands()
{
    COMMAND do_exit = COMMAND("exit", 
                                                    cmd_exit, 
                                                    "exit_doc", 
                                                    "exit_help");
    ReadlineWrap::getInstance()->addCommand(do_exit);
}
