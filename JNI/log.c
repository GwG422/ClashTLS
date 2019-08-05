/*
    Purpose: Clash of Streamers reversing stuff. idk man.
    Author: Reece W.
    License: Public MIT license | All Rights Reserved (2019) J. Reece Wilson (license@reece.sx). 
    Note: Code contained herein has either been derived via an implied license, developed as permitted by European law, and/or the vague definitions of fair dealing.
*/
#include "common.h"
#include "log.h"

typedef int(*AndroidLog_f)(int level, const char *tag, const char *fmt, ...);

int a_print(const char * str)
{
	static AndroidLog_f __android_log_print_real = 0;
	
	if (!__android_log_print_real)
		__android_log_print_real = dlsym(dlopen("liblog.so", RTLD_NOW), "__android_log_print");
	
	return __android_log_print_real(3, LOGGING_TAG, str);
}

int a_printf(const char * str, ...)
{
	int ret = 0;
	char * buffer;
	size_t length;
	va_list args;
	
	va_start(args, str);
	
	length = vsnprintf(NULL, 0, str, args);
	length ++;
	
	buffer = malloc(length);
	if (!buffer) 
		goto out;
	
	vsnprintf(buffer, length, str, args);
	
	ret = a_print(buffer);
	
	free(buffer);
	
out:
	va_end(args);
	return ret;
}

int a_vprintf(const char * str, va_list args)
{
	int ret = 0;
	char * buffer;
	size_t length;
	
	length = vsnprintf(NULL, 0, str, args);
	length ++;
	
	buffer = malloc(length);
	if (!buffer) 
		return 0;
	
	vsnprintf(buffer, length, str, args);
	
	ret = a_print(buffer);
	
	free(buffer);
	
	return ret;
}
