/*
    Purpose: Main logic
    Author: Reece W.
    License: Public MIT license | All Rights Reserved (2019) J. Reece Wilson (license@reece.sx). 
*/
#include "common.h"
#include "log.h"

static void init_load()
{
	PRINT_INFO("Hello world");
}

void init_tryload() 
{
	static bool loaded = false;
	if (loaded)
		return;
	loaded = true;
	
	init_load();
}

