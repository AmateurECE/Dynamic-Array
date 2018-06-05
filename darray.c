/******************************************************************************
 * NAME:	    darray.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    C source file for the Dynamic Array abstract type.
 *
 * CREATED:	    04/16/2018
 *
 * LAST EDITED:	    06/04/2018
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
 * MACRO DEFINITIONS
 ***/

#define Calculate(x) ((int)floor(log((x)/4 + 2) / log(2)) - 1)

/******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***/

static listelmt * get_landing(darray * array, int index, int expand);
static int expand_list(darray * array, int i);

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
    .size = 0,
    .last = NULL,
    .llanding = 0,
    .largest = 0,
    .landings = 0
  };

  if ((array->buckets = list_create(destroy)) == NULL) {
    free(array);
    return NULL;
  }

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
  if (array == NULL || index < 0 || index > array->largest)
    return NULL;

  /* Get the number of and a pointer to the landing */
  int num = Calculate(index);
  listelmt * l = get_landing(array, num, 0);
  if (l == NULL)
    return NULL;

  array->llanding = num;
  array->last = l;
  return ((void **)l->data)[index - num];
}

/******************************************************************************
 * FUNCTION:	    darray_set
 *
 * DESCRIPTION:	    Sets the element at the index `index' in `array'` to be the
 *		    pointer `data.'
 *
 * ARGUMENTS:	    array: (darray *) -- The array we would like to mutate.
 *		    index: (int) -- The index in the array.
 *		    data: (void *) -- The data to populate the array with.
 *
 * RETURN:	    int -- 0 if successful, -1 if something bad happened
 *
 * NOTES:	    O(logn), E(1) for multiple sequential accesses.
 *		    TODO: Update to decrease the size of the array if updating
 *			array[highest] to NULL.
 ***/
int darray_set(darray * array, int index, void * data)
{
  if (array == NULL || index < 0)
    return -1;
  /* This isn't an error...but we don't have to do anything if it's true */
  if (index > array->largest && data == NULL)
    return 0;

  /* Get the number of and a pointer to the landing */
  int num = Calculate(index);
  listelmt * l = get_landing(array, num, 1);

  if (index > array->largest)
    array->largest = index;

  array->llanding = num;
  array->last = l;
  array->size++;
  ((void **)l->data)[index - num] = data;
  return 0;
}

void darray_destroy(darray ** array)
{
  /* TODO: darray_destroy */
  return;
}

/******************************************************************************
 * STATIC FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    get_landing
 *
 * DESCRIPTION:	    Returns a pointer to the landing specified, optionally
 *		    expanding the list on the way up, if necessary.
 *
 * ARGUMENTS:	    array: (darray *) -- pointer to the array we're searching.
 *		    index: (int) -- The nth landing in the array.
 *		    expand: (int) -- non-zero if we are allowed to expand.
 *
 * RETURN:	    listelmt * -- Pointer to the landing.
 *
 * NOTES:	    O(logn), E(1) - Optimized for sequential access.
 ***/
static listelmt * get_landing(darray * array, int index, int expand)
{
  /* Get the index */
  listelmt * l = array->buckets->head;
  int i = 0;

  /* Figure out if we've been here before */
  if (index == array->llanding && array->last != NULL)
    l = array->last;
  else
    for (i = index; i > 0 && l != NULL; i--)
      l = l->next;

  /* We might be done here. If that's the case, return */
  if (l != NULL)
    return l;

  /* Expand the list if we are allowed to, and need to */
  if (expand && expand_list(array, i))
    return NULL;
  /* Navigate to the correct landing, now that we've initialized it. */
  l = array->buckets->head;
  for (i = index; i > 0 && l != NULL; i--)
    l = l->next;

  return l;
}

/******************************************************************************
 * FUNCTION:	    expand_list
 *
 * DESCRIPTION:	    Expands the array by `i' landings.
 *
 * ARGUMENTS:	    array: (darray *) -- The array to expand.
 *		    i: (int) -- The number of landings to add to the array.
 *
 * RETURN:	    int -- 0 on success, -1 on failure.
 *
 * NOTES:	    O(1)
 ***/
static int expand_list(darray * array, int i)
{
  if (i < 0)
    return -1;

  void ** data = NULL;
  while (i-- >= 0) {
    /* TODO: Check the floating point environment here */
    if ((data = calloc((size_t)pow(2.0, 3.0 + (double)array->landings++),
		       sizeof(void *))) == NULL)
      return -1;
    if (list_insnxt(array->buckets,
		    array->buckets->tail,
		    (void *)data) == -1) {
      free(data);
      return -1;
    }
  }

  return 0;
}

/*****************************************************************************/
