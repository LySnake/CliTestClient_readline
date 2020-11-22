#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <linux/limits.h>

#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include <utility>


#include "ReadlineWrap.h"
#include "utils.h"
#include "CommandList.h"
#include "spdlog/spdlog.h"

std::shared_ptr<ReadlineWrap> ReadlineWrap::instance = nullptr;
std::vector<Command> ReadlineWrap::vecCommands;

std::shared_ptr<ReadlineWrap> &ReadlineWrap::getInstance()
{
    if (instance == nullptr)
    {
        instance = std::shared_ptr<ReadlineWrap>(new ReadlineWrap());
        return instance;
    }
    return instance;
}


char ** ReadlineWrap::completion(const char* text, int start, int end)
{
  char **matches;

  matches = (char **)NULL;

  if (start == 0)
    matches = rl_completion_matches (text, &ReadlineWrap::generator);

  return (matches);
}

char * ReadlineWrap::generator(const char *text, int state)
{
  static int list_index, len;
  char *name;

  /* If this is a new word to complete, initialize now.  This includes
     saving the length of TEXT for efficiency, and initializing the index
     variable to 0. */
  if (!state)
    {
      list_index = 0;
      len = strlen (text);
    }

  /* Return the next name which partially matches from the command list. */
    for (;list_index < vecCommands.size();)
    {
        Command cmd = vecCommands[list_index];
        list_index++;
        
        if (strncmp (cmd.getCmdName().c_str(), text, len) == 0)
          return (dupstr(cmd.getCmdName().c_str()));
    }

  /* If no names matched, then return NULL. */
  return ((char *)NULL);
}


ReadlineWrap::ReadlineWrap():isRuningFlag(true)
{
    initialize();
}

void ReadlineWrap::initialize()
{
    rl_readline_name = READLINE_NAME;
    rl_attempted_completion_function = &ReadlineWrap::completion;
}

void ReadlineWrap::addCommand(Command &cmd)
{
    vecCommands.push_back(cmd);
}

void ReadlineWrap::stopReadline()
{
  isRuningFlag = false;
}

void ReadlineWrap::runReadline()
{
  char *line, *s;
  for ( ; isRuningFlag; )
    {
      char cwd[PATH_MAX];
      if( !getcwd(cwd, sizeof(cwd)))
      {
        spdlog::info("getcwd fail: {}\n", strerror(errno));
        return ;
      }
      char prompt [PATH_MAX + sizeof(READLINE_NAME)];
      sprintf(prompt, "%s>", cwd);
      line = readline (prompt );

      if (!line)
        break;

      /* Remove leading and trailing whitespace from the line.
         Then, if there is anything left, add it to the history list
         and execute it. */
      s = stripwhite (line);

      if (*s)
        {
          add_history (s);
          execute (s);
        }

      free (line);
    }
}

int ReadlineWrap::execute(char *line)
{
  int cmdStartIndex = 0, argsStartIndex;
  std::string cmdName;
  std::string args;

  while (line[cmdStartIndex] && whitespace (line[cmdStartIndex]))
    cmdStartIndex++;

  argsStartIndex = cmdStartIndex;
  while (line[argsStartIndex] && !whitespace (line[argsStartIndex]))
    argsStartIndex++;

  if (line[argsStartIndex])
    line[argsStartIndex++] = '\0';

  cmdName = line + cmdStartIndex;
  Command command = getCommand(cmdName);

  /* Get argument to command, if any. */
  while (whitespace (line[argsStartIndex]))
    argsStartIndex++;

  args = line + argsStartIndex;

  /* Call the function. */
  return command.runCmd(cmdName, args);
}

Command & ReadlineWrap::getCommand(const std::string &cmdName)
{
    for (auto &&cmd : vecCommands)
    {
        if(cmd.getCmdName() == cmdName)
        {
          return cmd;
        }
    }
    
    return cmd_fail;
}



