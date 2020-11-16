#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

#include <utility>


#include "ReadlineWrap.h"
#include "utils.h"
#include "Commands.h"
#include "threadPrint.h"   //模仿异步事件，打印到终端

static std::shared_ptr<ReadlineWrap> instance = nullptr;


ReadlineWrap::COMMAND::COMMAND(std::string name, rl_icpfunc_t func, std::string doc, std::string help):
                              CmdName(std::move(name)), CmdFunc(func), CmdDoc(std::move(doc)), CmdHelp(std::move(help))
{
}

const std::string &ReadlineWrap::COMMAND::getCmdName()
{
  return CmdName;
}

const std::string &ReadlineWrap::COMMAND::getCmdDoc()
{
  return CmdDoc;
}

const std::string &ReadlineWrap::COMMAND::getCmdHelp()
{
  return CmdHelp;
}

int ReadlineWrap::COMMAND::runCmd(char *line)
{
   CmdFunc(line);
}




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
        COMMAND cmd = vecCommands[list_index];
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

void ReadlineWrap::addCommand(COMMAND &cmd)
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
      line = readline (READLINE_NAME);

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
  register int i;
  char *word;

  /* Isolate the command word. */
  i = 0;
  while (line[i] && whitespace (line[i]))
    i++;
  word = line + i;

  while (line[i] && !whitespace (line[i]))
    i++;

  if (line[i])
    line[i++] = '\0';

  COMMAND command = getCommand(word);

  /* Get argument to command, if any. */
  while (whitespace (line[i]))
    i++;

  word = line + i;

  /* Call the function. */
  return command.runCmd(word);
}

ReadlineWrap::COMMAND & ReadlineWrap::getCommand(char *name)
{
    for (auto &&cmd : vecCommands)
    {
        if(cmd.getCmdName() == name)
        {
          return cmd;
        }
    }
    
    return cmd_fail;
}



