#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>

#ifdef READLINE_LIBRARY
#  include "readline.h"
#  include "history.h"
#else
#  include <readline/readline.h>
#  include <readline/history.h>
#endif

extern char *xmalloc PARAMS((size_t));

#ifndef whitespace
#define whitespace(c) (((c) == ' ') || ((c) == '\t'))
#endif

char *stripwhite(char * str);
char *dupstr(const char*);


#endif //__UTILS_H__