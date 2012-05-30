#ifndef __GLIM_DEBUG_H__
#define __GLIM_DEBUG_H__

/**
 * glim-debug.h
 *   Some debugging utilities.  Mostly macros that can be turned on or off.
 *     GOT_HERE() - Indicate that you reached a point in the program.
 *       (Useful when you don't have anything useful to print.)
 *     REPORT(string) - print a message
 *     REPORT_I(string) - print an integer expression
 *     REPORT_S(string) - print a string expression
 *     PREFIX - The prefix of messages.  Used by the REPORT* functions.
 *   Further details and utilities to follow.
 */

// +---------+--------------------------------------------------------
// | Headers |
// +---------+ 

#include <stdio.h>


// +--------+---------------------------------------------------------
// | Macros |
// +--------+ 

/**
 * A block of code.
 */
#define BLOCK(X) do { X } while (0)

/**
 * The standard prefix for output.
 */
#define PREFIX fprintf (stderr, "[%s:%d] ", __FILE__, __LINE__);

#ifdef DEBUG
#define REPORT(s) BLOCK (PREFIX; fprintf (stderr, "%s\n", s);)
#define REPORT_I(i) BLOCK (PREFIX; fprintf (stderr, "%s = %d\n", #i, i);)
#define REPORT_S(s) BLOCK (PREFIX; fprintf (stderr, "%s = %s\n", #s, s);)

#else
#define PREFIX
#define REPORT(s)
#define REPORT_I(i) 
#define REPORT_S(s) 
#endif

/**
 * We've arrived!
 */
#define GOT_HERE() REPORT("")

#endif // __GLIM_DEBUG_H__
