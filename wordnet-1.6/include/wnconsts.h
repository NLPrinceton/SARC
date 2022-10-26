/*

   wnconsts.h - constants used by all parts of WordNet system

   $Id: wnconsts.h,v 1.58 1997/11/13 19:41:51 wn Exp $

*/

#ifndef _WNCONSTS_
#define _WNCONSTS_

/* Platform specific path and filename specifications */

#ifdef UNIX
#define DICTDIR         "/dict"
#define DEFAULTPATH	"/usr/local/wordnet1.6/dict"
#define DEFAULTBIN      "/usr/local/wordnet1.6/bin"
#define DATAFILE	"%s/data.%s"
#define INDEXFILE	"%s/index.%s"
#define SENSEIDXFILE	"%s/index.sense"
#define COUSINFILE	"%s/cousin.tops"
#define COUSINEXCFILE	"%s/cousin.exc"
#define VRBSENTFILE     "%s/sents.vrb"
#define VRBIDXFILE	"%s/sentidx.vrb"
#endif
#ifdef PC
#define DICTDIR         "\\dict"
#define DEFAULTPATH	"c:\\wn16\\dict"
#define DEFAULTBIN      "c:\\wn16\\bin"
#define DATAFILE	"%s\\%s.dat"
#define INDEXFILE	"%s\\%s.idx"
#define SENSEIDXFILE	"%s\\sense.idx"
#define COUSINFILE	"%s\\cousin.tps"
#define COUSINEXCFILE	"%s\\cousin.exc"
#define VRBSENTFILE  	"%s\\sents.vrb"
#define VRBIDXFILE	"%s\\sentidx.vrb"
#endif
#ifdef MAC
#define DICTDIR         ":Database"
#define DEFAULTPATH     ":Database"
#define DEFAULTBIN      ":"
#define DATAFILE	"%s:data.%s"
#define INDEXFILE	"%s:index.%s"
#define SENSEIDXFILE	"%s:index.sense"
#define COUSINFILE	"%s:cousin.tops"
#define COUSINEXCFILE	"%s:cousin.exc"
#define VRBSENTFILE     "%s:sents.vrb"
#define VRBIDXFILE 	"%s:sentidx.vrb"
#endif

/* Various buffer sizes */

/* Search output buffer */
#ifdef UNIX
#define SEARCHBUF	((long)(200*(long)1024))
#endif
#ifdef MAC
#define SEARCHBUF	((long)(32*(long)1024))
#endif
#ifdef PC
#ifdef WINDOWS
#define SEARCHBUF	((long)(200*(long)1024))
#else
#define SEARCHBUF	((long)(32*(long)1024))
#endif
#endif

#define LINEBUF		(15*1024) /* 15K buffer to read index & data files */
#define SMLINEBUF	(3*1024) /* small buffer for output lines */
#define WORDBUF		(256)	/* buffer for one word or collocation */

#define ALLSENSES	0	/* pass to findtheinfo() if want all senses */
#define MAXID		15	/* maximum id number in lexicographer file */
#define MAXDEPTH	20	/* maximum tree depth - used to find cycles */
#define MAXSENSE	75	/* maximum number of senses in database */
#define MAX_FORMS	5	/* max # of different 'forms' word can have */
#define MAXFNUM		44	/* maximum number of lexicographer files */

/* Pointer type and search type counts */

#define MAXPTR		19
#define MAXSEARCH       29

/* Pointers */

#define ANTPTR           1	/* ! */
#define HYPERPTR         2	/* @ */
#define HYPOPTR          3	/* ~ */
#define ENTAILPTR        4	/* * */
#define SIMPTR           5	/* & */

#define ISMEMBERPTR      6	/* #m */
#define ISSTUFFPTR       7	/* #s */
#define ISPARTPTR        8	/* #p */

#define HASMEMBERPTR     9	/* %m */
#define HASSTUFFPTR     10	/* %s */
#define HASPARTPTR      11	/* %p */

#define MERONYM         12	/* % (not valid in lexicographer file) */
#define HOLONYM         13	/* # (not valid in lexicographer file) */
#define CAUSETO         14	/* > */
#define PPLPTR	        15	/* < */
#define SEEALSOPTR	16	/* ^ */
#define PERTPTR		17	/* \ */
#define ATTRIBUTE	18	/* = */
#define VERBGROUP	19	/* $ */

#define SYNS            (MAXPTR + 1)
#define FREQ            (MAXPTR + 2)
#define FRAMES          (MAXPTR + 3)
#define COORDS          (MAXPTR + 4)
#define RELATIVES	(MAXPTR + 5)
#define HMERONYM        (MAXPTR + 6)
#define HHOLONYM	(MAXPTR + 7)
#define WNESCORT	(MAXPTR + 8)
#define WNGREP		(MAXPTR + 9)
#define OVERVIEW	(MAXPTR + 10)

/* WordNet part of speech stuff */

#define NUMPARTS	4	/* number of parts of speech */
#define NUMFRAMES	35	/* number of verb frames */

/* Generic names for part of speech */

#define NOUN		1
#define VERB		2
#define ADJ		3
#define ADV		4
#define SATELLITE	5	/* not really a part of speech */
#define ADJSAT		SATELLITE

#define ALL_POS		0	/* passed to in_wn() to check all POS */

#define bit(n) ((unsigned long)((unsigned long)1<<((unsigned long)n)))

/* Adjective markers */

#define PADJ		1	/* (p) */
#define NPADJ		2	/* (n) */
#define IPADJ		3	/* (ip) */

#define UNKNOWN_MARKER		0
#define ATTRIBUTIVE		PADJ
#define IMMED_POSTNOMINAL	NPADJ
#define PREDICATIVE		IPADJ

#endif				/* _WNCONSTS_ */

