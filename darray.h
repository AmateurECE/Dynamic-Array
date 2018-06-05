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
 * LAST EDITED:	    06/04/2018
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

/* The number of non-NULL elements in the array.
 * This is an important distinction from darray_largest.
 */
#define darray_size(darray) ((darray)->size)

/* The largest index in the array pointing to a non-NULL element. */
#define darray_largest(darray) ((darray)->largest)

/* The number of landings in the array */
#define darray_landings(darray) ((darray)->landings)

/* The number returned by this macro is the total number of locations that
 * are currently allocated to the array. This is not the total amount of memory
 * consumed by the array.
 */
#define darray_capacity(darray) ((2 ** ((darray)->landings + 2)) - 8)

/******************************************************************************
 * TYPE DEFINITIONS
 ***/

typedef struct {

  list * buckets;
  int size;
  listelmt * last;
  int llanding;
  int largest;
  int landings;
  void (*destroy)(void *);

} darray;

/******************************************************************************
 * API FUNCTION PROTOTYPES
 ***/

extern darray * darray_create(void (*destroy)(void *));
extern void * darray_get(darray * array, int index);
extern int darray_set(darray * array, int index, void * data);
extern void darray_destroy(darray ** array);

#endif /* __ET_DARRAY_H__ */

/*****************************************************************************/
