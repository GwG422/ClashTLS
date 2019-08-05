/*
    Purpose: Random proxy stubs. Possibly used to mess with the games internals
    Author: Reece W.
    License: Public MIT license | All Rights Reserved (2019) J. Reece Wilson (license@reece.sx). 
*/
#include "common.h"
#include "main.h"
#include "log.h"
#include "init_hook.h"

void * get_unity_handle(void)
{
	static void * handle = NULL;
	
	if (handle)
		return handle;
	
	return handle = dlopen("libunity.so", RTLD_NOW);
}

void * get_il_handle(void)
{
	static void * handle = NULL;
	
	if (handle)
		return handle;
	
	return handle = dlopen("libil2cpp.so", RTLD_NOW);
}

static size_t il2cpp_init(const char * c)
{
	PRINT_TRACE;
	init_utf8();
	size_t ret = ((size_t(*)(const char * d))(dlsym(get_il_handle(), "il2cpp_init")))(c);
	init_post_utf8();
	return ret;
}

static size_t il2cpp_init_utf16(const void * c)
{
	PRINT_TRACE;
	size_t ret = ((size_t(*)(const void * d))(dlsym(get_il_handle(), "il2cpp_init_utf16")))(c);
	init_post_utf16();
	return ret;
}

static void * lookup_function(const char * name)
{
	if (strcmp(name, "il2cpp_init") == 0)
	{
		return il2cpp_init;
	} 
	else if (strcmp(name, "il2cpp_init_utf16") == 0)
	{
		return il2cpp_init_utf16;
	} 
	else 
	{
		return NULL;
	}
}

ELF_EXPORT void * utsym(void * handle, const char * name)
{
	void * ret;
	
	init_tryload();
	
	if (!(ret = lookup_function(name)))
		ret = dlsym(handle, name);
	
	PRINT_DEBUG("Unity looked up symbol: %s (0x%p)", name, ret);
	return ret;
}

ELF_EXPORT void * ilsym(void * handle, const char * name)
{
	void * ret;
	
	init_tryload();
	
	if (!(ret = lookup_function(name)))
		ret = dlsym(handle, name);
	
	PRINT_DEBUG("C# looked up symbol: %s (0x%p)", name, ret);
	return ret;
}