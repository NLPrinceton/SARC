/*

  license.h - WordNet license and copyright notice

*/

/* $Id: license.h,v 1.10 1997/08/28 17:15:20 wn Exp $ */

#ifdef unix

static char *license = "\
This software and database is being provided to you, the LICENSEE, by  \n\
Princeton University under the following license.  By obtaining, using  \n\
and/or copying this software and database, you agree that you have  \n\
read, understood, and will comply with these terms and conditions.:  \n\
  \n\
Permission to use, copy, modify and distribute this software and  \n\
database and its documentation for any purpose and without fee or  \n\
royalty is hereby granted, provided that you agree to comply with  \n\
the following copyright notice and statements, including the disclaimer,  \n\
and that the same appear on ALL copies of the software, database and  \n\
documentation, including modifications that you make for internal  \n\
use or for distribution.  \n\
  \n\
WordNet 1.6 Copyright 1997 by Princeton University.  All rights reserved.  \n\
  \n\
THIS SOFTWARE AND DATABASE IS PROVIDED \"AS IS\" AND PRINCETON  \n\
UNIVERSITY MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR  \n\
IMPLIED.  BY WAY OF EXAMPLE, BUT NOT LIMITATION, PRINCETON  \n\
UNIVERSITY MAKES NO REPRESENTATIONS OR WARRANTIES OF MERCHANT-  \n\
ABILITY OR FITNESS FOR ANY PARTICULAR PURPOSE OR THAT THE USE  \n\
OF THE LICENSED SOFTWARE, DATABASE OR DOCUMENTATION WILL NOT  \n\
INFRINGE ANY THIRD PARTY PATENTS, COPYRIGHTS, TRADEMARKS OR  \n\
OTHER RIGHTS.  \n\
  \n\
The name of Princeton University or Princeton may not be used in  \n\
advertising or publicity pertaining to distribution of the software  \n\
and/or database.  Title to copyright in this software, database and  \n\
any associated documentation shall at all times remain with  \n\
Princeton University and LICENSEE agrees to preserve same.  \n"
;
#else

static char *license[] = {
"This software and database is being provided to you, the LICENSEE, by  \n",
"Princeton University under the following license.  By obtaining, using  \n",
"and/or copying this software and database, you agree that you have  \n",
"read, understood, and will comply with these terms and conditions.:  \n  \n",
"Permission to use, copy, modify and distribute this software and  \n",
"database and its documentation for any purpose and without fee or  \n",
"royalty is hereby granted, provided that you agree to comply with  \n",
"the following copyright notice and statements, including the disclaimer,  \n",
"and that the same appear on ALL copies of the software, database and  \n",
"documentation, including modifications that you make for internal  \n",
"use or for distribution.  \n  \n",
"WordNet 1.6 Copyright 1997 by Princeton University.  All rights reserved.  \n  \n",
"THIS SOFTWARE AND DATABASE IS PROVIDED \"AS IS\" AND PRINCETON  \n",
"UNIVERSITY MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR  \n",
"IMPLIED.  BY WAY OF EXAMPLE, BUT NOT LIMITATION, PRINCETON  \n",
"UNIVERSITY MAKES NO REPRESENTATIONS OR WARRANTIES OF MERCHANT-  \n",
"ABILITY OR FITNESS FOR ANY PARTICULAR PURPOSE OR THAT THE USE  \n",
"OF THE LICENSED SOFTWARE, DATABASE OR DOCUMENTATION WILL NOT  \n",
"INFRINGE ANY THIRD PARTY PATENTS, COPYRIGHTS, TRADEMARKS OR  \n",
"OTHER RIGHTS.  \n  \n",
"The name of Princeton University or Princeton may not be used in  \n",
"advertising or publicity pertaining to distribution of the software  \n",
"and/or database.  Title to copyright in this software, database and  \n",
"any associated documentation shall at all times remain with  \n",
"Princeton University and LICENSEE agrees to preserve same.  \n", NULL};

#endif

static char dblicense[] = "\
  1 This software and database is being provided to you, the LICENSEE, by  \n\
  2 Princeton University under the following license.  By obtaining, using  \n\
  3 and/or copying this software and database, you agree that you have  \n\
  4 read, understood, and will comply with these terms and conditions.:  \n\
  5   \n\
  6 Permission to use, copy, modify and distribute this software and  \n\
  7 database and its documentation for any purpose and without fee or  \n\
  8 royalty is hereby granted, provided that you agree to comply with  \n\
  9 the following copyright notice and statements, including the disclaimer,  \n\
  10 and that the same appear on ALL copies of the software, database and  \n\
  11 documentation, including modifications that you make for internal  \n\
  12 use or for distribution.  \n\
  13   \n\
  14 WordNet 1.6 Copyright 1997 by Princeton University.  All rights reserved.  \n\
  15   \n\
  16 THIS SOFTWARE AND DATABASE IS PROVIDED \"AS IS\" AND PRINCETON  \n\
  17 UNIVERSITY MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR  \n\
  18 IMPLIED.  BY WAY OF EXAMPLE, BUT NOT LIMITATION, PRINCETON  \n\
  19 UNIVERSITY MAKES NO REPRESENTATIONS OR WARRANTIES OF MERCHANT-  \n\
  20 ABILITY OR FITNESS FOR ANY PARTICULAR PURPOSE OR THAT THE USE  \n\
  21 OF THE LICENSED SOFTWARE, DATABASE OR DOCUMENTATION WILL NOT  \n\
  22 INFRINGE ANY THIRD PARTY PATENTS, COPYRIGHTS, TRADEMARKS OR  \n\
  23 OTHER RIGHTS.  \n\
  24   \n\
  25 The name of Princeton University or Princeton may not be used in  \n\
  26 advertising or publicity pertaining to distribution of the software  \n\
  28 and/or database.  Title to copyright in this software, database and  \n\
  29 any associated documentation shall at all times remain with  \n\
  30 Princeton University and LICENSEE agrees to preserve same.  \n"
;

#define DBLICENSE_SIZE 	(sizeof(dblicense))

/*
  Revision log:

  $Log: license.h,v $
 * Revision 1.10  1997/08/28  17:15:20  wn
 * fixed typos
 *
 * Revision 1.9  1997/08/28  16:39:27  wn
 * updated for 1.6
 *
 * Revision 1.8  1995/02/07  16:11:06  wn
 * moved dblicense to outside ifdef
 *
 * Revision 1.7  1995/01/20  20:10:28  wn
 * added stuff to help find size of license and dbfiles
 *
 * Revision 1.6  1994/12/22  17:34:50  wn
 * updated for 1.5
 *
 * Revision 1.5  1993/07/01  16:34:27  wn
 * upgraded text to 1.4, 1993
 *
 * Revision 1.4  92/11/19  11:00:35  wn
 * updates for Mac and windows port
 * 
 * Revision 1.3  92/09/08  14:36:22  wn
 * update to 1.3 release 
 * 
 * Revision 1.2  92/03/26  11:16:48  wn
 * added WordNet version number
 * 
 * Revision 1.1  91/11/26  15:09:30  wn
 * Initial revision
 * 
 * Revision 1.1  91/09/11  14:43:27  wn
 * Initial revision
 * 
*/
