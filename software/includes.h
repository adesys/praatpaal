/**
 * @file    includes.h
 *          Generic include files
 *
 * @author  
 *
 * @date    18/05/2006
 *
 * @version
 **/

#ifndef __INCLUDES_H
#define __INCLUDES_H

#include <interrupt.h>
#include <io.h>
#include <wdt.h>
#include <stdbool.h>
#include <stddef.h>
#include <pgmspace.h>
#include <sfr_defs.h>
#include <stdlib.h>
#include <ctype.h>
#include <avrx.h>

#include "hardware.h"
#include "generic.h"
#include "types.h"
#include "os.h"

#define DECL_FUNC() \
    const char* func = __FUNCTION__;

#define DBG_PRINT(param)


#endif /* __INCLUDES_H */
