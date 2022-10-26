/* 

  wn.c - Command line interface to WordNet

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "wn.h"
#include "wnhelp.h"
#include "license.h"

static char *Id = "$Id: wn.c,v 1.58 1997/11/21 19:01:17 wn Exp $";

static struct {
    char *option;		/* user's search request */
    int search;			/* search to pass findtheinfo() */
    int pos;			/* part-of-speech to pass findtheinfo() */
    int helpmsgidx;		/* index into help message table */
    char *label;		/* text for search header message */
} *optptr, optlist[] = {
    { "-synsa", SIMPTR,	ADJ, 0, "Similarity" },
    { "-antsa", ANTPTR,	ADJ, 1, "Antonyms" },
    { "-perta", PERTPTR, ADJ, 0, "Pertainyms" },
    { "-famla", FREQ, ADJ, 3, "Familiarity" },
    { "-attra", ATTRIBUTE, ADJ, 2, "Attributes" },
    { "-grepa", WNGREP, ADJ, 4, "Grep" },
    { "-antsn", ANTPTR,	NOUN, 2, "Antonyms" },
    { "-hypen", -HYPERPTR, NOUN, 4, "Synonyms/Hypernyms (Ordered by Frequency)" },
    { "-hypon", HYPOPTR, NOUN, 5, "Hyponyms" },
    { "-meron", MERONYM, NOUN, 9, "Meronyms" },
    { "-holon", HOLONYM, NOUN, 7, "Holonyms" },
    { "-treen", -HYPOPTR, NOUN, 6, "Hyponyms" },
    { "-famln", FREQ, NOUN, 12, "Familiarity" },
    { "-synsn", HYPERPTR, NOUN, 0, "Synonyms/Hypernyms (Ordered by Frequency)" },
    { "-simsn", RELATIVES, NOUN, 1, "Synonyms (Grouped by Similarity of Meaning)" },
    { "-simsv", RELATIVES, VERB, 1, "Synonyms (Grouped by Similarity of Meaning)" },
    { "-subsn", HASSTUFFPTR, NOUN, 9, "Substance Meronyms" },
    { "-partn", HASPARTPTR, NOUN, 9, "Part Meronyms" },
    { "-membn", HASMEMBERPTR, NOUN, 9, "Member Meronyms" },
    { "-sprtn", ISPARTPTR, NOUN, 7, "Part Holonyms" },
    { "-smemn", ISMEMBERPTR, NOUN, 7, "Member Holonyms" },
    { "-ssubn", ISSTUFFPTR, NOUN, 7, "Substance Holonyms" },
    { "-hmern", -HMERONYM, NOUN, 10, "Meronyms" },
    { "-hholn",	-HHOLONYM, NOUN, 8, "Holonyms" },
    { "-coorn", COORDS, NOUN, 3, "Coordinate Terms" },
    { "-attrn", ATTRIBUTE, NOUN, 11, "Attributes" },
    { "-grepn", WNGREP, NOUN, 13, "Grep" },
    { "-antsv", ANTPTR, VERB, 1, "Antonyms" },
    { "-synsv", HYPERPTR, VERB, 0, "Synonyms/Hypernyms (Ordered by Frequency)" },
    { "-famlv", FREQ, VERB, 7, "Familiarity" },
    { "-hypev", -HYPERPTR, VERB, 2, "Synonyms/Hypernyms (Ordered by Frequency)" },
    { "-treev", -HYPOPTR, VERB, 3, "Hyponyms" },
    { "-hypov", HYPOPTR, VERB, 3, "Hyponyms" },
    { "-entav", ENTAILPTR, VERB, 4, "Entailment" },
    { "-framv", FRAMES, VERB, 6, "Sample Sentences" },
    { "-causv", CAUSETO, VERB, 5, "\'Cause To\'" },
    { "-grepv", WNGREP, VERB, 8, "Grep" },
    { "-synsr", SYNS, ADV, 0, "Synonyms" },
    { "-antsr", ANTPTR, ADV, 1, "Antonyms" },
    { "-pertr", PERTPTR, ADV, 0, "Pertainyms" },
    { "-famlr", FREQ, ADV, 2, "Familiarity" },
    { "-grepr", WNGREP, ADV, 3, "Grep" },
    { "-over", OVERVIEW, ALL_POS, -1, "Overview" },
    { NULL, 0, 0, 0, NULL }
};

struct {
    char *template;		/* template for generic search message */
    char *option;		/* text for help message */
    char *helpstr;	
} searchstr[] = {		/* index by search type type */
    { NULL, NULL, NULL },
    { "-ants%c",	"-ants{n|v|a|r}",	"\t\tAntonyms", },
    { "-hype%c",	"-hype{n|v}",	"\t\tHypernyms", },
    { "-hypo%c, -tree%c",	"-hypo{n|v}, -tree{n|v}",
	  "\tHyponyms & Hyponym Tree", },
    { "-enta%c",	"-entav",	"\t\t\tVerb Entailment", },
    { "-syns%c",	"-syns{n|v|a|r}",	"\t\tSynonyms (ordered by frequency)", },
    { "-smem%c",	"-smemn",	"\t\t\tMember of Holonyms", },
    { "-ssub%c",	"-ssubn",	"\t\t\tSubstance of Holonyms", },
    { "-sprt%c",	"-sprtn",	"\t\t\tPart of Holonyms", },
    { "-memb%c",	"-membn",	"\t\t\tHas Member Meronyms", },
    { "-subs%c",	"-subsn",	"\t\t\tHas Substance Meronyms", },
    { "-part%c",	"-partn",	"\t\t\tHas Part Meronyms", },
    { "-mero%c",	"-meron",	"\t\t\tAll Meronyms", },
    { "-holo%c",	"-holon",	"\t\t\tAll Holonyms", },
    { "-caus%c",	"-causv",	"\t\t\tVerb Cause to", },
    { NULL, NULL, NULL },	/* verb caused by - not used */
    { NULL, NULL, NULL },	/* see also - no specific search */
    { "-pert%c",	"-pert{a|r}",	"\t\tPertainyms", },
    { "-attr%c",	"-attr{n|a}",	"\t\tAttributes", },
    { NULL, NULL, NULL },	/* verb groups */
    { NULL, NULL, NULL },	/* syns - taken care of w/SIMPTR */
    { "-faml%c",	"-faml{n|v|a|r}",	"\t\tFamiliarity & Polysemy Count", },
    { "-fram%c",	"-framv",	"\t\t\tVerb Frames", },
    { "-coor%c",	"-coorn",	"\t\t\tCoordinate Sisters", },
    { "-sims%c",	"-sims{n|v}",	"\t\t\tSynonyms (grouped by similarity of meaning)", },
    { "-hmer%c",	"-hmern",	"\t\t\tHierarchical Meronyms", },
    { "-hhol%c", 	"-hholn",	"\t\t\tHierarchical Holonyms" },
    { NULL, NULL, NULL },	/* wnescort - used by xwn only */
    { "-grep%c",	"-grep{n|v|a|r}", "\t\tList of Compound Words" },
    { "-over", "-over", "\t\tOverview of Senses" },
};

static int getoptidx(char *), cmdopt(char *);
static int searchwn(int, char *[]);
static int do_search(char *, int, int, int, char *);
static int do_is_defined(char *);
static void printusage(), printlicense(),
       printsearches(char *, int, unsigned long);
static int error_message(char *);

main(int argc,char *argv[])
{
    int i;

    display_message = error_message;
    
    if (argc < 2) {
	printusage();
	exit(-1);
    } else if (argc == 2 && !strcmp("-l", argv[1])) {
	printlicense();
	exit(-1);
    }

    if (wninit()) {		/* open database */
	display_message("wn: Fatal error - cannot open WordNet database\n");
	exit (-1);
    }
    
    exit(searchwn(argc, argv));
}

static int searchwn(int ac, char *av[])
{
    int i, j = 1, pos;
    int whichsense = ALLSENSES, help = 0;
    int errcount = 0, outsenses = 0;
    char tmpbuf[256];		/* buffer for constuction error messages */
    
    if (ac == 2)		/* print available searches for word */
	exit(do_is_defined(av[1]));

    /* Parse command line options once and set flags */

    dflag = fileinfoflag = offsetflag = wnsnsflag = 0;

    for(i = 1; i < ac; i++) {
	if(!strcmp("-g",av[i]))
	    dflag++;
	else if (!strcmp("-h",av[i]))
	    help++;
	else if (!strcmp("-l", av[i]))
	    printlicense();
	else if (!strncmp("-n", av[i], 2))
	    whichsense = atoi(av[i] + 2);
	else if (!strcmp("-a", av[i]))
	    fileinfoflag = 1;
	else if (!strcmp("-o", av[i]))
	    offsetflag = 1;
	else if (!strcmp("-s", av[i]))
	    wnsnsflag = 1;
    }

    /* Replace spaces with underscores before looking in database */

    strtolower(strsubst(av[1], ' ', '_'));

    /* Look at each option in turn.  If it's not a command line option
       (which was processed earlier), perform the search requested. */

    while(av[++j]) {
	if (!cmdopt(av[j])) {	/* not a command line option */
	    if ((i = getoptidx(av[j])) != -1) {
		optptr = &optlist[i];

		/* print help text before search output */
		if (help && optptr->helpmsgidx >= 0)
		    printf("%s\n", helptext[optptr->pos][optptr->helpmsgidx]);

		if (optptr->pos == ALL_POS)
		    for (pos = 1; pos <= NUMPARTS; pos++)
			outsenses += do_search(av[1], pos, optptr->search,
						whichsense, optptr->label);
		else
		    outsenses += do_search(av[1], optptr->pos, optptr->search,
					    whichsense, optptr->label);
	    } else {
		sprintf(tmpbuf, "wn: invalid search option: %s\n", av[j]);
		display_message(tmpbuf);
		errcount++;
	    }
	}
    }
    return(errcount ? -errcount : outsenses);
}

static int do_search(char *searchword, int pos, int search, int whichsense,
		     char *label)
{
    int totsenses = 0;
    char *morphword, *outbuf;

    outbuf = findtheinfo(searchword, pos, search, whichsense);
    totsenses += wnresults.printcnt;
    if (strlen(outbuf) > 0)
	printf("\n%s of %s %s\n%s",
	       label, partnames[pos], searchword, outbuf);

    if (morphword = morphstr(searchword, pos))
	do {
	    outbuf = findtheinfo(morphword, pos, search, whichsense);
	    totsenses += wnresults.printcnt;
	    if (strlen(outbuf) > 0) 
		printf("\n%s of %s %s\n%s",
		       label, partnames[pos], morphword, outbuf);
	} while (morphword = morphstr(NULL, pos));

    return(totsenses);
}

static int do_is_defined(char *searchword)
{
    int i, found = 0;
    unsigned long search;
    char *morphword;

    if (searchword[0] == '-') {
	display_message("wn: invalid search word\n");
	return(-1);
    }
    
    /* Print all valid searches for word in all parts of speech */

    strtolower(strsubst(searchword, ' ', '_'));
	    
    for (i = 1; i <= NUMPARTS; i++) {
	if ((search = is_defined(searchword, i)) != 0) {
	    printsearches(searchword, i, search);
	    found = 1;
	} else
	    printf("\nNo information available for %s %s\n",
		   partnames[i], searchword);

	if ((morphword = morphstr(searchword, i)) != NULL)
	    do {
		if ((search = is_defined(morphword, i)) != 0) {
		    printsearches(morphword, i, search);
		    found = 1;
		} else
		    printf("\nNo information available for %s %s\n",
			   partnames[i], morphword);
	    } while ((morphword = morphstr(NULL, i)) != NULL );
    }
    return(found);
}

static void printsearches(char *word, int dbase, unsigned long search)
{
    int j;

    printf("\nInformation available for %s %s\n", partnames[dbase], word);
    for (j = 1; j <= MAXSEARCH; j++)
	if ((search & bit(j)) && searchstr[j].option) {
	    printf("\t");
	    printf(searchstr[j].template,
		   partchars[dbase], partchars[dbase]);
	    printf(searchstr[j].helpstr);
	    printf("\n");
	}
}

static void printusage()
{
    int i;

    fprintf(stdout,
	    "\nusage: wn word [-hgla] [-n#] -searchtype [-searchtype...]\n");
    fprintf(stdout, "       wn [-l]\n\n");
    fprintf(stdout, "\t-h\t\tDisplay help text before search output\n");
    fprintf(stdout, "\t-g\t\tDisplay gloss\n");
    fprintf(stdout, "\t-l\t\tDisplay license and copyright notice\n");
    fprintf(stdout, "\t-a\t\tDisplay lexicographer file information\n");
    fprintf(stdout, "\t-o\t\tDisplay synset offset\n");
    fprintf(stdout, "\t-s\t\tDisplay sense numbers in synsets\n");
    fprintf(stdout, "\t-n#\t\tSearch only sense number #\n");
    fprintf(stdout,"\nsearchtype is at least one of the following:\n");

    for (i = 1; i <= MAXSEARCH; i++)
	if (searchstr[i].option)
	    fprintf(stdout, "\t%s%s\n",
		    searchstr[i].option, searchstr[i].helpstr);
}

static void printlicense()
{
    printf("WordNet Release %s\n\n", wnrelease);
    printf(license);
}

static int cmdopt(char *str)
{
    if(strcmp("-g", str) && strcmp("-h", str) && strcmp("-o", str) &&
       strcmp("-l", str) && strncmp("-n", str, 2) && strcmp("-a", str) &&
       strcmp("-s", str))
	return(0);
    else
	return(1);
}


static int getoptidx(char *searchtype)
{
    int i;

    for (i = 0; optlist[i].option; i++)
	if (!strcmp(optlist[i].option, searchtype))
	    return(i);

    return(-1);
}

static int error_message(char *msg)
{
    fprintf(stderr, msg);
    return(0);
}

/*
  Revision log: (since version 1.5)
  
  $Log: wn.c,v $
 * Revision 1.58  1997/11/21  19:01:17  wn
 * added simsv search
 *
 * Revision 1.57  1997/09/02  17:10:32  wn
 * changed includes
 *
 * Revision 1.56  1997/08/29  18:43:37  wn
 * rearranged functions
 *
 * Revision 1.55  1997/08/29  16:44:24  wn
 * added code to exit with total senses printed
 *
 * Revision 1.54  1997/08/26  20:29:38  wn
 * added -s option, reorganized code
 *
 * Revision 1.53  1997/08/08  19:19:03  wn
 * major cleanup
 *
 * Revision 1.52  1997/08/05  20:15:31  wn
 * removed WNDEBUG, cleanups
 *
 * Revision 1.51  1995/06/30  19:25:02  wn
 * access first element of OutSenseCount array
 *
  * 
  * Revision 1.1  91/09/17  15:51:09  wn
  * Initial revision
  * 
  */

