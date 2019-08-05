/*
    Purpose: Clash of Streamers reversing stuff. idk man.
    Author: Reece W.
    License: Public MIT license | All Rights Reserved (2019) J. Reece Wilson (license@reece.sx). 
    Note: Code contained herein has either been derived via an implied license, developed as permitted by European law, and/or the vague definitions of fair dealing.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <jni.h>
#include <dlfcn.h>
#include <pthread.h>

#define ELF_EXPORT JNIEXPORT

#include "config.h"