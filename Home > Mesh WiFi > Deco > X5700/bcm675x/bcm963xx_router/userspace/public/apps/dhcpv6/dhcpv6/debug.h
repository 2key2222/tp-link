#ifndef MY_DEBUG_H_
#define MY_DEBUG_H_

/* switch to enable/disable debug */
//#define dbg

#ifdef dbg
/* First include stdio.h, which may contain the prototype for the external dprintf.
 * We do not want that. We redefine dprintf to our local implementation. */
#include <stdio.h>
#define dprintf my_dprintf
#ifndef __P
# define __P(x) x
#endif
extern void my_dprintf __P((int, const char *, const char *, ...));
#else
#define dprintf
#endif

#endif /* MY_DEBUG_H_ */
