#include <string.h>
#include "utils.h"

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
