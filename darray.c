/******************************************************************************
 * NAME:	    darray.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    C source file for the Dynamic Array abstract type.
 *
 * CREATED:	    04/16/2018
 *
 * LAST EDITED:	    04/29/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
 * NOTES:	    O(1)
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

/******************************************************************************
 * FUNCTION:	    darray_get
 *
 * DESCRIPTION:	    Return the user field stored in the dynamic array at the
 *		    index.
 *
 * ARGUMENTS:	    array: (darray *) -- Pointer to the array in question.
 *		    index: (int) -- Index desired.
 *
 * RETURN:	    void * -- Pointer to the user field.
 *
 * NOTES:	    O(logn), E(1) for multiple sequential accesses.
 ***/
void * darray_get(darray * array, int index)
{
  if (array == NULL || index < 0)
    return NULL;

  /* Get the bucket number we're looking for */
  listelmt * l = array->buckets->head;
  int num = ((int)floor(log2(index)) >> 1) & 0xfe;

  /* Check if we've been here before */
  if (num == array->llanding && array->last != NULL)
    l = array->last;
  else
    for (int i = num; i >= 0 && l != NULL; i--)
      l = l->next;

  if (l == NULL)
    return NULL;

  array->llanding = num;
  array->last = l;
  return ((void **)l->data)[index - num];
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
