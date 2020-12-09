#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>

#ifndef whitespace
#define whitespace(c) (((c) == ' ') || ((c) == '\t'))
#endif

namespace tool {
    char *stripwhite(char * str);
    char *dupstr(const char*);

    void Backtrace(size_t depth = 1);
} //namespace tool

#endif //__UTILS_H__