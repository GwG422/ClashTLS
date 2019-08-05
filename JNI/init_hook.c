/*
    Purpose: il2cpp_init_xxx hooks and patches
    Author: Reece W.
    License: Public MIT license | All Rights Reserved (2019) J. Reece Wilson (license@reece.sx). 
*/
#include "common.h"
#include <stdint.h>
#include "log.h"
#include "init_hook.h"
#include "syms.h"
#include "unity.h"

typedef struct Il2CppObject
{
    union
    {
        Il2CppClass *klass;
        void *vtable;
    };
    void *monitor;
} Il2CppObject;

typedef Il2CppDomain *    (* il2cpp_domain_get_f)           ();
typedef Il2CppAssembly ** (* il2cpp_domain_get_assemblies_f)(const Il2CppDomain * domain, size_t * size);
typedef Il2CppClass  *    (* il2cpp_class_from_name_f)      (const Il2CppImage * image, const char* namespaze, const char *name);
typedef Il2CppObject *    (* il2cpp_object_new_f)           (const Il2CppClass * klass);

static il2cpp_domain_get_f            il2cpp_domain_get;
static il2cpp_domain_get_assemblies_f il2cpp_domain_get_assemblies;
static il2cpp_class_from_name_f       il2cpp_class_from_name;
static il2cpp_object_new_f            il2cpp_object_new;

static void lookup_syms(void)
{
	il2cpp_class_from_name       = dlsym(get_il_handle(), "il2cpp_class_from_name");
	il2cpp_domain_get_assemblies = dlsym(get_il_handle(), "il2cpp_domain_get_assemblies");
	il2cpp_domain_get            = dlsym(get_il_handle(), "il2cpp_domain_get");
	il2cpp_object_new            = dlsym(get_il_handle(), "il2cpp_object_new");
}

[...]

static size_t hooked(size_t a, size_t b, size_t c, size_t d, size_t e /*, size_t f NULL*/)
{
	// i dont feel safe working with this ABI :(
	return 1;
}

static void patch_telepathy_pinning(Il2CppClass * class)
{
	il2cpp_object_new(class); // poke il2cpp otherwise the class may not be initialized

	if (!class->methods)
		return;
	
	for (size_t i = 0; i < class->method_count; i++)
	{
		MethodInfo * method = (/* remove const */ MethodInfo *) class->methods[i];
		
		if (!method)
			continue;
		
		if (strcmp(method->name, "DefaultCertificateValidationCallback"))
			continue;
		
		method->methodPointer = hooked;
		break;
	}
}

void patch_crypto_common(void)
{
	size_t cnt;
	Il2CppDomain * domain;
	Il2CppAssembly ** asms;
	
	domain = il2cpp_domain_get();
	asms   = il2cpp_domain_get_assemblies(domain, &cnt);
	
	for (size_t i = 0; i < cnt; i++)
	{
		Il2CppClass * client;
		
		if (client = il2cpp_class_from_name(asms[i]->image, "Telepathy", "Client"))
			patch_telepathy_pinning(client);
	}
}

void patch_crypto(void)
{
	//patch_crypto_common();
}

void patch_crypto_proactive(void)
{
	patch_crypto_common();
}

static void init_post(void) 
{
	PRINT_DEBUG("IL2CPP has loaded!");
	
	lookup_syms();
	patch_crypto_proactive();
	
	PRINT_DEBUG("Let's try dumping the game >>>:)");
	dump();
}

void init_utf8(void)
{
	
}

void init_post_utf16(void)
{
	// il2cpp_init_utf16 isn't used as far as i know
	// I don't even know a safe way to kill an android app from here. 
	// Let's just sigfault
	*(int*)0xff = 0xff;	
}

void init_post_utf8(void)
{
	init_post();
}