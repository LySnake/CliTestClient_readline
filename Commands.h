#ifndef __COMMANDS_H__
#define __COMMANDS_H__
#include "ReadlineWrap.h"


using COMMAND = ReadlineWrap::COMMAND;

void initializeCommands();

extern COMMAND cmd_fail;

#endif //__COMMANDS_H__