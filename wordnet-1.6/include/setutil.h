/*
   setutil.h - Functions for creating and working with sets.
               Used in WordNet library to find noun relatives

   $Id: setutil.h,v 1.2 1997/09/02 16:31:18 wn Exp $

*/

#ifndef _SETUTIL_
#define _SETUTIL_

typedef struct set_tag *Set_t;

Set_t set_create(unsigned max_elem);
Set_t set_resize(Set_t s, unsigned new_max_elem);
void  set_destroy(Set_t s);

void set_addobj(Set_t s, unsigned objnum);    /*s += obj.*/
void set_removeobj(Set_t s, unsigned objnum); /*s -= obj.*/  

void set_union(Set_t u, Set_t a, Set_t b);        /* u = a + b.*/
void set_intersection(Set_t n, Set_t a, Set_t b); /* u = a x b.*/

int set_nelem(Set_t s);   /*returns |s|.*/
int set_isempty(Set_t s); /* returns |s| == 0.*/
int set_haselem(Set_t s, unsigned objnum); /* returns obj E s ?*/ 
int set_maxelem(Set_t s); /*Returns max num of elems set can hold.*/

#endif /* SET_UTIL */
