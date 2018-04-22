/******************************************************************************
 * NAME:	    darray.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    C source file for the Dynamic Array abstract type.
 *
 * CREATED:	    04/16/2018
 *
 * LAST EDITED:	    04/22/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>

#include "list.h"
#include "darray.h"

/******************************************************************************
 * API FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    darray_create
 *
 * DESCRIPTION:	    Create a new darray structure and return a pointer to it.
 *
 * ARGUMENTS:	    destroy: (void (*)(void *)) User-defined function which
 *			frees any memory used by a user field.
 *
 * RETURN:	    (darray *) -- Pointer to a new darray struct, or NULL.
 *
 * NOTES:	    none.
 ***/
darray * darray_create(void (*destroy)(void *))
{
  darray * array = NULL;
  if ((array = malloc(sizeof(darray))) == NULL)
    return NULL;

  *array = (darray){
    .buckets = list_create(destroy),
    .size = 0,
    .last = NULL,
    .llanding = 0,
    .stairs = 8,
    .landings = 1
  };

  void ** land = NULL;
  if ((land = calloc(8, sizeof(void *))) == NULL) {
    list_destroy(&(array->buckets));
    free(array);
  }

  list_insnxt(array->buckets,
	      list_head(array->buckets),
	      (void *)land);
  return array;
}

void * darray_get(darray * array, int index)
{
  /* TODO: darray_get */
  return NULL;
}

int darray_set(darray * array, int index, void * data)
{
  /* TODO: darray_set */
  return -1;
}

void darray_destroy(darray ** array)
{
  /* TODO: darray_destroy */
  return;
}

/*****************************************************************************/
