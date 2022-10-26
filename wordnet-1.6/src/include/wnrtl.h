/*
   
   wnrtl.h - global variables

   $Id: wnrtl.h,v 1.1 1997/09/02 16:31:18 wn Exp $

*/

#ifndef _WNRTL_
#define _WNRTL_

#include <stdio.h>
#include "wnconsts.h"
#include "wntypes.h"

/* Global variables and flags */

extern SearchResults wnresults;	/* structure containing results of search */
extern int fnflag;		/* if set, print lex filename after sense */
extern int dflag;		/* if set, print definitional glosses */
extern int saflag;		/* if set, print SEE ALSO pointers */
extern int fileinfoflag;	/* if set, print lex file info on synsets */
extern int frflag;		/* if set, print verb frames after synset */
extern int abortsearch;		/* if set, stop search algorithm */
extern int offsetflag;		/* if set, print byte offset of each synset */
extern int wnsnsflag;		/* if set, print WN sense # for each word */

/* File pointers for database files */

extern int OpenDB;		/* if non-zero, database file are open */
extern FILE *datafps[NUMPARTS + 1], 
            *indexfps[NUMPARTS + 1],
            *sensefp, 
            *cousinfp, *cousinexcfp, 
            *vidxfilefp, *vsentfilefp;

/* Method for interface to check for events while search is running */

extern void (*interface_doevents_func)(void);  
                        /* callback for interruptable searches in */
                        /* single-threaded interfaces */

/* General error message handler - can be defined by interface.
   Default function provided in library returns -1 */

extern int default_display_message(char *);
extern int (*display_message)(char *);

#endif /* _WNRTL_ */
