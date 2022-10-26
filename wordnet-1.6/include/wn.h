/*
   
   wn.h - header file needed to use WordNet Run Time Library

   $Id: wn.h,v 1.50 1997/09/02 16:31:18 wn Exp $

*/

#ifndef _WN_
#define _WN_

#include "wnconsts.h"
#include "wntypes.h"
#include "wnglobal.h"
#include "wnrtl.h"

/* External library function prototypes */

/*** Search and database functions (search.c) ***/

/* Primry search algorithm for use with user interfaces */
extern char *findtheinfo(char *, int, int, int);	

/* Primary search algorithm for use with programs (returns data structure) */
extern SynsetPtr findtheinfo_ds(char *, int, int, int); 

/* Set bit for each search type that is valid for the search word
   passed and return bit mask. */
extern unsigned long is_defined(char *, int); 

/* Set bit for each POS that search word is in.  0 returned if
   word is not in WordNet. */
extern unsigned int in_wn(char *, int);	

/* Find word in index file and return parsed entry in data structure.
   Input word must be exact match of string in database. */
extern IndexPtr index_lookup(char *, int); 

/* 'smart' search of index file.  Find word in index file, trying different
   techniques - replace hyphens with underscores, replace underscores with
   hyphens, strip hyphens and underscores, strip periods. */
extern IndexPtr getindex(char *, int);	

/* Read synset from data file at byte offset passed and return parsed
   entry in data structure. */
extern SynsetPtr read_synset(int, long, char *);

/* Read synset at current byte offset in file and return parsed entry
   in data structure. */
extern SynsetPtr parse_synset(FILE *, int, char *); 

/* Free a synset linked list allocated by findtheinfo_ds() */
extern void free_syns(SynsetPtr);	

/* Free a synset */
extern void free_synset(SynsetPtr);	

/* Free an index structure */
extern void free_index(IndexPtr);	

/* Recursive search algorithm to trace a pointer tree and return results
   in linked list of data structures. */
SynsetPtr traceptrs_ds(SynsetPtr, int, int, int);

/* Do requested search on synset passed, returning output in buffer. */
extern char *do_trace(SynsetPtr, int, int, int);

/*** Morphology functions (morph.c) ***/

/* Open exception list files */
extern int morphinit();	

/* Close exception list files and reopen */
extern int re_morphinit();	

/* Try to find baseform (lemma) of word or collocation in POS. */
extern char *morphstr(char *, int);	

/* Try to find baseform (lemma) of individual word in POS. */
extern char *morphword(char *, int);	

/*** Utility functions (wnutil.c) ***/

/* Top level function to open database files, initialize wn_filenames,
   and open exeception lists. */
extern int wninit();		

/* Top level function to close and reopen database files, initialize
   wn_filenames and open exception lists. */
extern int re_wninit();	

/* Count the number of underscore or space separated words in a string. */
extern int cntwords(char *, char);		

/* Convert string to lower case remove trailing adjective marker if found */
extern char *strtolower(char *);	

/* Convert string passed to lower case */
extern char *ToLowerCase(char *);	

/* Replace all occurrences of 'from' with 'to' in 'str' */
extern char *strsubst(char *, char, char);	

/* Return pointer code for pointer type characer passed. */
extern int getptrtype(char *);	

/* Return part of speech code for string passed */
extern int getpos(char *);		

/* Return synset type code for string passed. */
extern int getsstype(char *);		

/* Reconstruct synset from synset pointer and return ptr to buffer */
extern char *FmtSynset(SynsetPtr, int);	

/* Find string for 'searchstr' as it is in index file */
extern char *GetWNStr(char *, int);

/* Pass in string for POS, return corresponding integer value */
extern int StrToPos(char *);

/* Return synset for sense key passed. */
extern SynsetPtr GetSynsetForSense(char *);

/* Find offset of sense key in data file */
extern long GetDataOffset(char *);

/* Find polysemy (collins) count for sense key passed. */
extern int GetPolyCount(char *);

/* Return word part of sense key */
extern char *GetWORD(char *);

/* Return POS code for sense key passed. */
extern int GetPOS(char *);

/* Convert WordNet sense number passed of IndexPtr entry to sense key. */
extern char *WNSnsToStr(IndexPtr, int);

/* Search for string and/or baseform of word in database and return
   index structure for word if found in database. */
extern IndexPtr GetValidIndexPointer(char *, int);

/* Return sense number in database for word and lexsn passed. */
int GetWNSense(char *, char *);

SnsIndexPtr GetSenseIndex(char *);

/*
** Wrapper functions for strstr that allow you to retrieve each
** occurance of a word within a longer string, not just the first.
**
** strstr_init is called with the same arguments as normal strstr,
** but does not return any value.
**
** strstr_getnext returns the position offset (not a pointer, as does
** normal strstr) of the next occurance, or -1 if none remain.
*/
extern void strstr_init (char *, char *);
extern int strstr_getnext (void);

/*** Binary search functions (binsearch.c) ***/

/* General purpose binary search function to search for key as first
   item on line in open file.  Item is delimited by space. */
extern char *bin_search(char *, FILE *);

/* Copy contents from one file to another. */
extern void copyfile(FILE *, FILE *);

/* Function to replace a line in a file.  Returns the original line,
   or NULL in case of error. */
extern char *replace_line(char *, char *, FILE *);

/* Find location to insert line at in file.  If line with this
   key is already in file, return NULL. */
extern char *insert_line(char *, char *, FILE *);

#endif /*_WN_*/
