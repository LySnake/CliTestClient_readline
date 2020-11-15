#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>


#include <utility>
#include "threadPrint.h"   //模仿异步事件，打印到终端

static td::shared_ptr<ReadlineWrap> instance = nullptr;


ReadlineWrap::COMMAND::COMMAND(std::string name, rl_icpfunc_t *func, std::string doc, std::string help):CmdName(std::move(name)), CmdFunc(func), CmdDoc(std::move(doc), CmdHelp(std::move(help)))
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
    for (; i < list_index < listCommands.size();)
    {
        COMMAND cmd = listCommands[list_index];
        list_index++;
        
        if (strncmp (cmd.getCmdName().c_str(), text, len) == 0)
          return (dupstr(cmd.getCmdName().c_str()));
    }

  /* If no names matched, then return NULL. */
  return ((char *)NULL);
}


ReadlineWrap::ReadlineWrap()
{
    initialize();
}

void ReadlineWrap::initialize()
{
    rl_readline_name = READLINE_NAME;
    rl_attempted_completion_function = &ReadlineWrap::completion;
}

void ReadlineWrap::(COMMAND &cmd)
{
    listCommands.push_back(cmd);
}




// typedef struct {
//   char *name;			/* User printable name of the function. */
//   rl_icpfunc_t *func;		/* Function to call to do the job. */
//   char *doc;			/* Documentation for this function.  */
// } COMMAND;

// int com_cd (char *arg)
// {
//   if (chdir (arg) == -1)
//     {
//       perror (arg);
//       return 1;
//     }

//   com_pwd ("");
//   return (0);
// }

// COMMAND commands[] = {
//   { "cd", com_cd, "Change to directory DIR" },
//   { (char *)NULL, (rl_icpfunc_t *)NULL, (char *)NULL }
// };

// void valid_argument(char* caller, char* arg)
// {
//   if (!arg || !*arg)
//     {
//       fprintf (stderr, "%s: Argument required.\n", caller);
//       return (0);
//     }

//   return (1);
// }





int main(int argc, char *argv[])
{
    initializeReadline();

    StartThread();
  /* Loop reading and executing lines until the user quits. */
  for ( ; done == 0; )
    {
      line = readline ("FileMan: ");

      if (!line)
        break;

      /* Remove leading and trailing whitespace from the line.
         Then, if there is anything left, add it to the history list
         and execute it. */
      s = stripwhite (line);

      if (*s)
        {
          add_history (s);
          execute_line (s);
        }

      free (line);
    }
  StopThread();
  exit (0);

}
