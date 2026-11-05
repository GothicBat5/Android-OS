#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <obstack.h>

int __attribute__((__format__(printf, 2, 3)))  obstack_printf(struct obstack *obs, const char *format, ...) 
{
  va_list ap;
  va_start(ap, format);
  char* str = NULL;
  int len = vasprintf(&str, format, ap);
  
  if (len < 0) 
  {
    return len;
  }
  
  obstack_grow(obs, str, len);
  free(str);
  
  return len;
}
