#ifndef __DEFS_H
#define __DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#ifndef bool
//enum _bool {false = 0, true = 1};
//typedef enum _bool bool;
//#endif
#ifndef bool
typedef int bool;
#define true  1
#define false 0
#endif

#define NAME_LENGTH 256

#endif /* __DEFS_H */
