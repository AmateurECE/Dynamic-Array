/******************************************************************************
 * NAME:	    test.c
 *
 * AUTHOR:	    Ethan D. Twardy
 *
 * DESCRIPTION:	    Test source for the Dynamic Array abstract type.
 *
 * CREATED:	    04/16/2018
 *
 * LAST EDITED:	    04/18/2018
 ***/

/******************************************************************************
 * INCLUDES
 ***/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>

#include "darray.h"

/******************************************************************************
 * MACRO DEFINITIONS
 ***/

#define FAIL	"\033[1;31m"
#define NC	"\033[0m"

/* This is to alleviate portability issues */
#ifdef __APPLE__
#   define PASS	"\033[1;32m"
#else
#   define PASS "\033[1;39m"
#endif

#ifdef CONFIG_TEST_LOG
#   ifndef CONFIG_LOG_FILENAME
#	define CONFIG_LOG_FILENAME "./log.txt"
#   endif

#   define log(...) fprintf(logfile, __VA_ARGS__)
#   define log_fail(...) {			\
    log(__VA_ARGS__);				\
    log("\n");					\
    failures++;					\
    return 1;					\
  }

#   define CONFIG_LOG_PREAMBLE			\
  "MODULE - TEST LOG\n"				\
  "%s\n"					\
  "============================\n\n"

#else /* CONFIG_TEST_LOG */

#   define log(...)
#   define log_fail(...) { return 0; }

#endif /* CONFIG_TEST_LOG */

#define error_exitf(str, ...) {			\
    fprintf(stderr, str, __VA_ARGS__);		\
    printf("\n");				\
    exit(1);					\
  }
#define error_exit(str) {			\
    fprintf(stderr, str);			\
    printf("\n");				\
    exit(1);					\
  }

/******************************************************************************
 * GLOBAL VARIABLES
 ***/

#ifdef CONFIG_TEST_LOG
static FILE * logfile;
#endif

static int failures;

/******************************************************************************
 * STATIC FUNCTION PROTOTYPES
 ***/

static int test_get();
static int test_set();
static int test_create();
static int test_destroy();
static darray * prep_darray(int random);

/******************************************************************************
 * MAIN
 ***/

int main()
{
  srand((unsigned)time(NULL));

#ifdef CONFIG_TEST_LOG
  /* Initialize log here */
  printf("Initializing log in'"CONFIG_LOG_FILENAME"'...\n");
  if ((logfile = fopen(CONFIG_LOG_FILENAME, "w")) == NULL)
    error_exitf("Could not initialize log file: %s\n", strerror(errno));
  char * buff = NULL;
  if ((buff = malloc(64)) == NULL)
    error_exit("Could not allocate space for time buffer.");
  time_t raw;
  time(&raw);
  strftime(buff, 63, "%+", localtime(&raw));
  log(CONFIG_LOG_PREAMBLE, buff);
  free(buff);
#endif

  fprintf(stderr,

	  "Test (darray_get):\t%s\n"
	  "Test (darray_set):\t%s\n"
	  "Test (darray_create):\t%s\n"
	  "Test (darray_destroy):\t%s\n",

	  test_get()	    ? FAIL"Fail"NC : PASS"Pass"NC,
	  test_set()	    ? FAIL"Fail"NC : PASS"Pass"NC,
	  test_create()	    ? FAIL"Fail"NC : PASS"Pass"NC,
	  test_destroy()    ? FAIL"Fail"NC : PASS"Pass"NC);

#ifdef CONFIG_TEST_LOG
  fprintf(logfile, "\nFailures: %d\nEND OF LOG\n", failures);
  printf("Closing log file...\n");
  fclose(logfile);
#endif

  return failures;
}

/******************************************************************************
 * STATIC FUNCTIONS
 ***/

/******************************************************************************
 * FUNCTION:	    test_get
 *
 * DESCRIPTION:	    Tests the "darray_get()" function by probing with edge
 *		    cases, and cases which may expose holes in the
 *		    implementation logic.
 *
 * ARGUMENTS:	    void.
 *
 * RETURN:	    int -- 0 if the tests pass, 1 if they fail.
 *
 * NOTES:	    none.
 ***/
static int test_get() {

  /* Test 1 -- NULL input */
  darray * array = NULL;
  if (darray_get(array, 0) != NULL)
    log_fail("test_get: 1 failed--not NULL");

  /* Test 2 -- index less than 0 */
  if ((array = prep_darray(0)) == NULL)
    log_fail("\tFailure occurred in test_get: Test 2");
  if (darray_get(array, -1) != NULL)
    log_fail("test_get: 2 failed--not NULL");

  /* Test 3 -- get(0) is valid */
  if (*(int *)darray_get(array, 0) != 9)
    log_fail("test_get: 3 failed--!9");

  /* Test 4 -- get(1) is valid */
  if (*(int *)darray_get(array, 1) != 8)
    log_fail("test_get: 4 failed--!8");

  /* Test 5 -- get(size + 1) == 0 */
  if (*(int *)darray_get(array, darray_size(array) + 1) != 0)
    log_fail("test_get: 5 failed--!0");

  /* Test 6 -- get(size + 512) == 0 */
  int old = array->landings;
  if (*(int *)darray_get(array, darray_size(array) + 512) != 0)
    log_fail("test_get: 6 failed--!0");
  if (array->landings != old)
    log_fail("test_get: 6 failed--changed landings");

  /* Test 7 -- last = NULL; get(0)=get(0) */
  array->last = NULL;
  if (*(int *)darray_get(array, 0) != 9)
    log_fail("test_get: 7 failed--!9");

  return 0;
}

/******************************************************************************
 * FUNCTION:	    test_set
 *
 * DESCRIPTION:	    Tests the "darray_set()" function by probing with edge
 *		    cases.
 *
 * ARGUMENTS:	    void.
 *
 * RETURN:	    int -- 0 if the tests pass, 1 if they fail.
 *
 * NOTES:	    none.
 ***/
static int test_set() {

  /* Test 1 NULL inputs */
  int num = 0;
  if ((darray_set(NULL, 0, &num)))

  /* set(0) <-- Return valid
   * set(1) <-- Return valid
   * set(size + 1) <-- 0
   * set(size + 512) <-- 0
   * landings = NULL; set(0) <-- set(0)
   */
  return 1;
}

/******************************************************************************
 * FUNCTION:	    test_create
 *
 * DESCRIPTION:	    Tests the darray_create() function by probing.
 *
 * ARGUMENTS:	    void.
 *
 * RETURN:	    int -- 0 if the tests pass, 1 if they fail.
 *
 * NOTES:	    none.
 ***/
static int test_create() {
  /* Tests:
   * (NULL inputs)
   * create(std)
   */
  return 1;
}

/******************************************************************************
 * FUNCTION:	    test_destroy
 *
 * DESCRIPTION:	    Test the darray_destroy() function by probing.
 *
 * ARGUMENTS:	    void.
 *
 * RETURN:	    int -- 0 if the tests pass, 1 if they fail.
 *
 * NOTES:	    none.
 ***/
static int test_destroy() {
  /* Tests:
   * (NULL inputs)
   * destroy(real)
   * destroy(empty)
   */
  return 1;
}

/******************************************************************************
 * FUNCTION:	    prep_darray
 *
 * DESCRIPTION:	    Prepare a Dynamic Array with some random data for testing.
 *
 * ARGUMENTS:	    random: (int) -- if !0, fill the darray with random data.
 *
 * RETURN:	    darray * -- Pointer to a new dynamic array struct.
 *
 * NOTES:	    none.
 ***/
static darray * prep_darray(int random)
{
  darray * array = NULL;
  if ((array = darray_create(free)) == NULL) {
    log("prep_darray: darray_create returned NULL\n");
    return NULL;
  }

  int tmp[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

  int * pNum = NULL;
  for (int i = 0; i < 10; i++) {
    pNum = malloc(sizeof(int));
    if (random)
      *pNum = rand() % 10;
    else
      *pNum = tmp[i];
    darray_set(array, i, (void *)pNum);
  }

  if (darray_size(array) <= 0) {
    log("prep_darray: darray_size is <= 0\n");
    return NULL;
  }

  return array;
}

/*****************************************************************************/
