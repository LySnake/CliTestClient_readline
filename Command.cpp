#include "Command.h"
#include "project.h"


Command::Command(std::string name, EXEC_CMD_FUNC func, std::string doc, std::string help):
                              CmdName(std::move(name)), CmdFunc(func), CmdDoc(std::move(doc)), CmdHelp(std::move(help))
{
}

const std::string &Command::getCmdName()
{
  return CmdName;
}

const std::string &Command::getCmdDoc()
{
  return CmdDoc;
}

const std::string &Command::getCmdHelp()
{
  return CmdHelp;
}

int Command::runCmd(const std::string &cmdName, const std::string &args)
{
   CmdFunc(cmdName, args);
}
