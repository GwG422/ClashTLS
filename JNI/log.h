/*
    Purpose: Clash of Streamers reversing stuff. idk man.
    Author: Reece W.
    License: Public MIT license | All Rights Reserved (2019) J. Reece Wilson (license@reece.sx). 
    Note: Code contained herein has either been derived via an implied license, developed as permitted by European law, and/or the vague definitions of fair dealing.
*/

extern int a_print(const char * str);
extern int a_printf(const char * str, ...);
extern int a_vprintf(const char * str, va_list args);

#define PRINT_DEBUG(str, ...) a_printf("DEBUG: " str, ##__VA_ARGS__);
#define PRINT_INFO(str, ...)  a_printf("INFO : " str, ##__VA_ARGS__);
#define PRINT_WARN(str, ...)  a_printf("WARN : " str, ##__VA_ARGS__);
#define PRINT_TRACE           a_printf("ENTER: %s", __FUNCTION__);