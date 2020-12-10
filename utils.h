#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>

#ifndef whitespace
#define whitespace(c) (((c) == ' ') || ((c) == '\t'))
#endif


#ifdef __cplusplus
extern "C" {
    namespace tool {
#endif
        char *stripwhite(char * str);
        char *dupstr(const char*);

        void Backtrace(size_t depth = 1);
    
#ifdef __cplusplus
    } //namespace tool
}
#endif

#endif //__UTILS_H__