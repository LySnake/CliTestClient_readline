#include <string.h>
#include <execinfo.h>
#include <stdlib.h>
#include <string>
#include <sstream>

#include "ReadlineWrap.h"
#include "utils.h"
#include "project.h"

constexpr size_t MAX_TRACE_DEEP = 20;
constexpr size_t BUFF_SIZE = 1024;
const std::string FILENAME = "testClient";
#ifdef __cplusplus
namespace tool {
#endif
      char *dupstr (const char *s)
      {
        char *r;

        r = xmalloc (strlen (s) + 1);
        strcpy (r, s);
        return (r);
      }

      char *stripwhite(char *str)
      {
        register char *s, *t;

        for (s = str; whitespace (*s); s++)
          ;
          
        if (*s == 0)
          return (s);

        t = s + strlen (s) - 1;
        while (t > s && whitespace (*t))
          t--;
        *++t = '\0';

        return s;
      }
      
      void Backtrace(size_t depth)
      {
          void *array[MAX_TRACE_DEEP];
          size_t size;
          char **strings;
          size_t i;

          size = backtrace(array, MAX_TRACE_DEEP);
          strings = backtrace_symbols(array, size);
          if (NULL == strings)
          {
              perror("backtrace_synbols");
              return;
          }

          for (i = depth; i < size; i++) {
              char buf[BUFF_SIZE];
              std::stringstream cmd;
              cmd << "addr2line " << array[i] << " -e " << FILENAME << " -fisp";
              FILE *p_Pip = popen(cmd.str().c_str(), "r");
              if(!p_Pip) {
                  perror("popen fail.");
                  continue;
              }

              char *str = fgets(buf, sizeof(buf), p_Pip);
              if(str != buf) {
                  perror("fgets fail.");
                  pclose(p_Pip);
                  continue;
              }

              printf("%s", str);
              pclose(p_Pip);
          }
      }
#ifdef __cplusplus
  } // namespace tool
#endif