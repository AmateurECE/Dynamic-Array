/******************************************************************************
 * NAME:	    darray.h
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Header file containing public functions and supporting
 *		    macros for manipulating object of the darray abstract type.
 *
 * CREATED:	    04/16/2018
 *
 * LAST EDITED:	    04/18/2018
 ***/

#ifndef __ET_DARRAY_H__
#define __ET_DARRAY_H__

/******************************************************************************
 * INCLUDES
 ***/

#include "list.h"

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define darray_size(darray) ((darray)->size)

/* The number of stairs until we reach the next landing */
#define darray_stairs(darray) /* TODO: darray_stairs */

/* If we fell from our current height, the landing that we would end up on. */
#define darray_landing(darray) /* TODO: darray_landing */

#define darray_capacity(darray) /* TODO: darray_capacity */

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct {

  list * buckets;
  int size;
  void ** last;
  int llanding;
  int stairs;
  int landings;

} darray;

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

extern darray * darray_create(void (*destroy)(void *));
extern void * darray_get(darray * array, int index);
extern int darray_set(darray * array, int index, void * data);
extern void darray_destroy(darray * array);

#endif /* __ET_DARRAY_H__ */

/*****************************************************************************/