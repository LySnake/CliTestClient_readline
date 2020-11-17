#ifndef __UTILS_H__
#define __UTILS_H__


#ifndef whitespace
#define whitespace(c) (((c) == ' ') || ((c) == '\t'))
#endif

char *stripwhite(char * str);
char *dupstr(const char*);


#endif //__UTILS_H__