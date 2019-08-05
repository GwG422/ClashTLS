/*
    Purpose: For now, we just proxy liblog.so with dlopen/dlsym & modify the elfs to get into the processes address space.
			 Implements proxy log stuff!
    Author: Reece W.
    License: Public MIT license | All Rights Reserved (2019) J. Reece Wilson (license@reece.sx). 
*/
#include "common.h"
#include "log.h"
#include "main.h"

ELF_EXPORT 
int __android_log_write(
  int prio,
  const char *tag,
  const char *text
)
{
	init_tryload();
	return a_printf(" %i, %s: %s", prio, tag, text);
}

ELF_EXPORT 
int __android_log_vprint(
  int prio,
  const char *tag,
  const char *text,
  va_list ap
)
{
	int ret = 0;
	char * buffer;
	size_t length;
	
	init_tryload();
	
	length = vsnprintf(NULL, 0, text, ap);
	length ++;
	
	buffer = malloc(length);
	if (!buffer) 
		goto out;
	
	vsnprintf(buffer, length, text, ap);
	
	ret = a_print(buffer);
	
	free(buffer);
	
out:
	return ret;
}

ELF_EXPORT 
int __android_log_print(
  int prio,
  const char *tag,
  const char *fmt,
  ...
)
{
	int ret = 0;
	char * buffer;
	size_t length;
	va_list args;
	
	init_tryload();
	
	va_start(args, fmt);
	
	length = vsnprintf(NULL, 0, fmt, args);
	length ++;
	
	buffer = malloc(length);
	if (!buffer) 
		goto out;
	
	vsnprintf(buffer, length, fmt, args);
	
	ret = a_print(buffer);
	
	free(buffer);
	
out:
	va_end(args);
	return ret;
}